
/* Necessary includes for device drivers */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <asm/system.h> /* cli(), *_flags */
#include <asm/uaccess.h> /* copy_from/to_user */
#include <linux/timer.h>
#include <linux/string.h>
#include <asm-arm/arch-pxa/pxa-regs.h>
#include <asm-arm/arch-pxa/hardware.h>
#include <asm-arm/arch-pxa/gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

MODULE_LICENSE("Dual BSD/GPL");

#define GPIO_BUTTON_0 117
#define GPIO_BUTTON_1 101
#define GPIO_BUTTON_2 118
#define GPIO_BUTTON_3 28

/* Declaration of memory.c functions */
static int tetrix_open(struct inode *inode, struct file *filp);
static int tetrix_release(struct inode *inode, struct file *filp);
static ssize_t tetrix_read(struct file *filp,
		char *buf, size_t count, loff_t *f_pos);
static ssize_t tetrix_write(struct file *filp,
		const char *buf, size_t count, loff_t *f_pos);
static int tetrix_fasync(int fd, struct file *filp, int mode);
static void tetrix_exit(void);
static int tetrix_init(void);

/* Structure that declares the usual file */
/* access functions */
struct file_operations tetrix_fops = {
	read: tetrix_read,
	write: tetrix_write,
	open: tetrix_open,
	release: tetrix_release
	fasync: tetrix_fasync
};

/* Declaration of the init and exit functions */
module_init(tetrix_init);
module_exit(tetrix_exit);

/* Global variables of the driver */
/* Major number */
static int tetrix_major = 61;

struct fasync_struct *async_queue;  /* asynchronous readers */

/* Buffer to store data */
static char *tetrix_buffer;
/* length of the current message */
static int tetrix_len;

/////////////////////////////
static unsigned int capacity = 1000;

////////////////////////////

irqreturn_t gpio0_irq(int irq, void *dev_id, struct pt_regs *regs)
{
	if (async_queue)
		kill_fasync(&async_queue, SIGIO, POLL_IN);
	return IRQ_HANDLED;
}

irqreturn_t gpio1_irq(int irq, void *dev_id, struct pt_regs *regs)
{	
	if (async_queue)
		kill_fasync(&async_queue, SIGIO, POLL_IN);
	return IRQ_HANDLED;
}

irqreturn_t gpio2_irq(int irq, void *dev_id, struct pt_regs *regs)
{	
	if (async_queue)
		kill_fasync(&async_queue, SIGIO, POLL_IN);
	return IRQ_HANDLED;
}

irqreturn_t gpio3_irq(int irq, void *dev_id, struct pt_regs *regs)
{	
	if (async_queue)
		kill_fasync(&async_queue, SIGIO, POLL_IN);
	return IRQ_HANDLED;
}

static int tetrix_init(void)
{
	int result;

	/* Registering device */
	result = register_chrdev(tetrix_major, "tetrix", &tetrix_fops);
	if (result < 0)
	{
		printk(KERN_ALERT
			"tetrix: cannot obtain major number %d\n", tetrix_major);
		return result;
	}

	/* Allocating tetrix for the buffer */
	tetrix_buffer = kmalloc(capacity, GFP_KERNEL); 
	if (!tetrix_buffer)
	{ 
		printk(KERN_ALERT "Insufficient kernel memory\n"); 
		result = -ENOMEM;
		goto fail; 
	} 
	memset(tetrix_buffer, 0, capacity);
	tetrix_len = 0;

	//Setting up GPIO
	gpio_direction_input(GPIO_BUTTON_0);
	gpio_direction_input(GPIO_BUTTON_1);
	gpio_direction_input(GPIO_BUTTON_2);
	gpio_direction_input(GPIO_BUTTON_3);

	//Setting up interrupts
	int irq0 = IRQ_GPIO(GPIO_BUTTON_0);
	int irq1 = IRQ_GPIO(GPIO_BUTTON_1);
	int irq2 = IRQ_GPIO(GPIO_BUTTON_2);
	int irq3 = IRQ_GPIO(GPIO_BUTTON_3);

	if (request_irq(irq0, &gpio0_irq, SA_INTERRUPT | SA_TRIGGER_RISING,
				"button0", NULL) != 0 || 
	    request_irq(irq1, &gpio1_irq, SA_INTERRUPT | SA_TRIGGER_RISING,
				"button1", NULL) != 0 ||
		request_irq(irq2, &gpio2_irq, SA_INTERRUPT | SA_TRIGGER_RISING,
				"button2", NULL) != 0 ||
		request_irq(irq3, &gpio3_irq, SA_INTERRUPT | SA_TRIGGER_RISING,
				"button3", NULL) != 0) {
		printk ( "irq not acquired \n" );
		return -1;
    }else{
		printk ( "irq %d, irq %d, irq %d and irq %d acquired successfully \n", irq0, irq1, irq2, irq3 );
	}

	printk(KERN_ALERT "Inserting tetrix module\n"); 
	return 0;

fail: 
	tetrix_exit(); 
	return result;
}

static void tetrix_exit(void)
{
	/* Freeing the major number */
	unregister_chrdev(tetrix_major, "tetrix");

	/* Freeing buffer memory */
	if (tetrix_buffer)
	{
		kfree(tetrix_buffer);
	}
	
	/* Releasing interrupts */
	free_irq(IRQ_GPIO(GPIO_BUTTON_0), NULL);
	free_irq(IRQ_GPIO(GPIO_BUTTON_1), NULL);
	free_irq(IRQ_GPIO(GPIO_BUTTON_2), NULL);
	free_irq(IRQ_GPIO(GPIO_BUTTON_3), NULL);

	printk(KERN_ALERT "Removing tetrix module\n");

}

static int tetrix_open(struct inode *inode, struct file *filp)
{
	/* Success */
	return 0;
}

static int tetrix_release(struct inode *inode, struct file *filp)
{
	/* Success */
	tetrix_fasync(-1, filp, 0);
	return 0;
}

static ssize_t tetrix_read(struct file *filp, char *buf, 
							size_t count, loff_t *f_pos)
{ 
	char buffer[1000] = "";
	
	// if position beyond buffer length, STOP PRINTING
	if (*f_pos >= strlen(buffer)-1)
		return 0;

	// send buffer to user space
	if (copy_to_user(buf, buffer, strlen(buffer))){
		printk(KERN_INFO "KERN: Copy to user error!!\n");
		return -EFAULT;
	}

	(*f_pos) += (size_t) strlen(buffer);
	return strlen(buffer);	
}

static ssize_t tetrix_write(struct file *filp, const char *buf,
							size_t count, loff_t *f_pos)
{
	/* end of buffer reached */
    if (*f_pos >= capacity)
    {
        printk(KERN_INFO "write called: process id %d, command %s, count %d, buffer full\n", current->pid, current->comm, count);
        return -ENOSPC;
    }

    /* do not go over the end */
    if (count > capacity - *f_pos)
        count = capacity - *f_pos;

    // Get data from user space
	if (copy_from_user(tetrix_buffer + *f_pos, buf, count)){
		return -EFAULT;
	}

	// Retrieve first user sequence, ending w/ a space
	char tbuf[256], *tbptr = tbuf;
	int temp;
	for (temp = *f_pos; temp < count + *f_pos; temp++){
		if (tetrix_buffer[temp] == ' ' || tetrix_buffer[temp] == '\n')
			break;
		tbptr += sprintf(tbptr, "%c", tetrix_buffer[temp]);
	}

	
	(*f_pos) += count;
	return count;	
}

static int tetrix_fasync(int fd, struct file *filp, int mode) {
	return fasync_helper(fd, filp, mode, &async_queue);
}
