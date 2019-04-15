
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
#define GPIO_LED_0 16
#define GPIO_LED_1 29
#define GPIO_LED_2 30
#define GPIO_LED_3 31

/* Declaration of memory.c functions */
static int mygpio_open(struct inode *inode, struct file *filp);
static int mygpio_release(struct inode *inode, struct file *filp);
static ssize_t mygpio_read(struct file *filp,
		char *buf, size_t count, loff_t *f_pos);
static ssize_t mygpio_write(struct file *filp,
		const char *buf, size_t count, loff_t *f_pos);
static void mygpio_exit(void);
static int mygpio_init(void);
void display_binary(void);
void timer_handler(unsigned long data);


/* Structure that declares the usual file */
/* access functions */
struct file_operations mygpio_fops = {
	read: mygpio_read,
	write: mygpio_write,
	open: mygpio_open,
	release: mygpio_release
};

/* Declaration of the init and exit functions */
module_init(mygpio_init);
module_exit(mygpio_exit);

/* Global variables of the driver */
/* Major number */
static int mygpio_major = 61;

/* Buffer to store data */
static char *mygpio_buffer;
/* length of the current message */
static int mygpio_len;

/*List of GPIO LED */
static int mygpio_led[4] = {GPIO_LED_0, GPIO_LED_1, GPIO_LED_2, GPIO_LED_3};

/////////////////////////////
static unsigned int capacity = 1000;
int direction = 0; // 0 - up, 1 - down
int state = 0; // 0 - continue, 1 - stop
int period = 100;
int counter = 1;
struct timer_list timer;
// Timers for BTN0 & BTN1 simultaneous pressing
struct timer_list BTN0_timer;
struct timer_list BTN1_timer;
int tol_margin = 500;
int level = 0;
char speed[2] = "M";
////////////////////////////
void BTN0_timer_handler(unsigned long data){
	if (jiffies <= BTN1_timer.expires){ // if BTN1 pressed recently
		counter = 15;
		del_timer_sync(&BTN1_timer); // prevent BTN1 timer handler from being called
	} else 
		state = !state;
	return;
}
void BTN1_timer_handler(unsigned long data){
	if (jiffies <= BTN0_timer.expires){ // if BTN0 pressed recently
		counter = 15;
		del_timer_sync(&BTN0_timer); // prevent BTN0 timer handler from being called
	} else 
		direction = !direction;
	return;
}
irqreturn_t gpio0_irq(int irq, void *dev_id, struct pt_regs *regs)
{
	//no debounce, active for both edges

   	// Set timer to check simultaneous button presses
	mod_timer(&BTN0_timer, jiffies + msecs_to_jiffies(tol_margin));   
	return IRQ_HANDLED;
}

irqreturn_t gpio1_irq(int irq, void *dev_id, struct pt_regs *regs)
{	
	//no debounce, active for both edges

   	// Set timer to check simultaneous button presses
   	mod_timer(&BTN1_timer, jiffies + msecs_to_jiffies(tol_margin));   

	return IRQ_HANDLED;
}

void display_binary(void){
	// decimal to binary
	static char bin[5];
	int led = 0;
	bin[0] = '\0';
	unsigned int mask =  0x8; // 4 bit num with most sig bit as 1
	// bitwise AND and shift
	while (mask > 0){
		if ((counter & mask) == 0){
			strcat(bin, "0");
			if (led == 3)
				pwm_level(4); // goes to default - LEDs off
			else
				pxa_gpio_set_value(mygpio_led[3 - led], 0);
		}else{
			strcat(bin, "1");
			if (led == 3)
				pwm_level(level);
			else
				pxa_gpio_set_value(mygpio_led[3 - led], 1);
		}
		mask = mask >> 1;
		led++;
	}
	//printk(KERN_INFO "Number: %i, %s\n", counter, bin);
}

void timer_handler(unsigned long data){
	//Get button states
	//state = pxa_gpio_get_value(GPIO_BUTTON_0);
	//direction = pxa_gpio_get_value(GPIO_BUTTON_1);
	//printk(KERN_INFO "state: %i direction %i\n", state, direction);
	// if BTN0 isn't pressed, hold current state
	if (state != 0){
		// BTN1 controls direction of count
		if (direction != 0){ // pressed - count up
			if (counter == 15)
				counter = 1;
			else
				counter++;
		}else{ // released - count down
			if (counter == 1)
				counter = 15;
			else
				counter--;
		} 
	}
	//printk("Counter: %i\n", counter);
	mod_timer(&timer, jiffies + msecs_to_jiffies(period * 10));
	display_binary();
}

void pwm_level(int level){
	switch(level){
		case 0:
			//printk(KERN_INFO "Setting 0\n");
			PWM_CTRL0 = 0x001;
			PWM_PWDUTY0 = 0x001;
			PWM_PERVAL0 = 0x001;
			break;
		case 1:	
			//printk(KERN_INFO "Setting 1\n");
			PWM_CTRL0 = 0x001;
			PWM_PWDUTY0 = 0x001;
			PWM_PERVAL0 = 0x006;
			break;
		case 2:
			//printk(KERN_INFO "Setting 2\n");
			PWM_CTRL0 = 0x001;
			PWM_PWDUTY0 = 0x001;
			PWM_PERVAL0 = 0x030;
			break;
		default:
			PWM_CTRL0 = 0;
			PWM_PWDUTY0 = 0;
			PWM_PERVAL0 = 0x001;
	}
}

irqreturn_t pwm_irq(int irq, void *dev_id, struct pt_regs *regs)
{
	if (level == 2)
		level = 0;
	else
		level++;
	return IRQ_HANDLED;
}


static int mygpio_init(void)
{
	int result;

	/* Registering device */
	result = register_chrdev(mygpio_major, "mygpio", &mygpio_fops);
	if (result < 0)
	{
		printk(KERN_ALERT
			"mygpio: cannot obtain major number %d\n", mygpio_major);
		return result;
	}

	/* Allocating mygpio for the buffer */
	mygpio_buffer = kmalloc(capacity, GFP_KERNEL); 
	if (!mygpio_buffer)
	{ 
		printk(KERN_ALERT "Insufficient kernel memory\n"); 
		result = -ENOMEM;
		goto fail; 
	} 
	memset(mygpio_buffer, 0, capacity);
	mygpio_len = 0;

	// Setting timer
	setup_timer(&timer, timer_handler, 0);
	mod_timer(&timer, jiffies + msecs_to_jiffies(period * 10));

	setup_timer(&BTN0_timer, BTN0_timer_handler, 0);
	setup_timer(&BTN1_timer, BTN1_timer_handler, 0);

	//Setting up GPIO
	gpio_direction_input(GPIO_BUTTON_0);
	gpio_direction_input(GPIO_BUTTON_1);
	gpio_direction_input(GPIO_BUTTON_2);
	gpio_direction_output(GPIO_LED_0, 0);
	gpio_direction_output(GPIO_LED_1, 0);
	gpio_direction_output(GPIO_LED_2, 0);
	gpio_direction_output(GPIO_LED_3, 0);

	//Setting up interrupts
	int irq0 = IRQ_GPIO(GPIO_BUTTON_0);
	int irq1 = IRQ_GPIO(GPIO_BUTTON_1);
	int irq2 = IRQ_GPIO(GPIO_BUTTON_2);

	if (request_irq(irq0, &gpio0_irq, SA_INTERRUPT | SA_TRIGGER_RISING,
				"button0", NULL) != 0 || 
	    request_irq(irq1, &gpio1_irq, SA_INTERRUPT | SA_TRIGGER_RISING,
				"button1", NULL) != 0 ||
		 request_irq(irq2, &pwm_irq, SA_INTERRUPT | SA_TRIGGER_RISING,
				"pwm_button", NULL) != 0) {
                printk ( "irq not acquired \n" );
                return -1;
        }else{
                printk ( "irq %d, irq %d, and irq %d acquired successfully \n", irq0, irq1, irq2 );
	}

	//set up GPIO alternative function
	pxa_gpio_mode(GPIO16_PWM0_MD);
	pxa_set_cken(CKEN0_PWM0, 1);

	printk(KERN_ALERT "Inserting mygpio module\n"); 
	return 0;

fail: 
	mygpio_exit(); 
	return result;
}

static void mygpio_exit(void)
{
	/* Freeing the major number */
	unregister_chrdev(mygpio_major, "mygpio");

	/* Freeing buffer memory */
	if (mygpio_buffer)
	{
		kfree(mygpio_buffer);
	}
	
	/* Releasing interrupts */
	free_irq(IRQ_GPIO(GPIO_BUTTON_0), NULL);
	free_irq(IRQ_GPIO(GPIO_BUTTON_1), NULL);
	free_irq(IRQ_GPIO(GPIO_BUTTON_2), NULL);

	printk(KERN_ALERT "Removing mygpio module\n");

}

static int mygpio_open(struct inode *inode, struct file *filp)
{
	/* Success */
	return 0;
}

static int mygpio_release(struct inode *inode, struct file *filp)
{
	/* Success */
	return 0;
}

static ssize_t mygpio_read(struct file *filp, char *buf, 
							size_t count, loff_t *f_pos)
{ 
	char buffer[1000] = "";
	char dir_str[10];
	char state_str[10];
	char level_str[2];

	// Get direction	
	if (direction != 0)
		strcpy(dir_str, "Up");
	else
		strcpy(dir_str, "Down");

	// Get state
	if (state != 0)
		strcpy(state_str, "Count");
	else
		strcpy(state_str, "Hold");
	// Get brightness
	if (level == 0)
		strcpy(level_str, "H");
	else if (level == 1)
		strcpy(level_str, "M");
	else	
		strcpy(level_str, "L");
	// Create buffer 
	//sprintf(buffer, "Value: %i\nPeriod: %i.%i\nDirection: %s\nState: %s\n", counter, period / 100, period % 100, dir_str, state_str);
	sprintf(buffer,"%i\n%s\n%s\n%s\n%s\n", counter, speed, state_str, dir_str, level_str);
	
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

static ssize_t mygpio_write(struct file *filp, const char *buf,
							size_t count, loff_t *f_pos)
{
	/* end of buffer reached */
        if (*f_pos >= capacity)
        {
                printk(KERN_INFO
                        "write called: process id %d, command %s, count %d, buffer full\n",
                        current->pid, current->comm, count);
                return -ENOSPC;
        }

        /* do not go over the end */
        if (count > capacity - *f_pos)
                count = capacity - *f_pos;

        // Get data from user space
	if (copy_from_user(mygpio_buffer + *f_pos, buf, count)){
		return -EFAULT;
	}

	// Retrieve first user sequence, ending w/ a space
	char tbuf[256], *tbptr = tbuf;
	int temp;
	for (temp = *f_pos; temp < count + *f_pos; temp++){
		if (mygpio_buffer[temp] == ' ' || mygpio_buffer[temp] == '\n')
			break;
		tbptr += sprintf(tbptr, "%c", mygpio_buffer[temp]);
	}
	// Parse data
	if (tbuf[0] == 'f'){ // Change period
		strcpy(speed, tbuf+1);
		int dec;
		if(speed[0] == 'H')
			dec = 1;
		else if(speed[0] == 'M')
			dec = 4;
		else if(speed[0] == 'L')
			dec = 9;
		else
			printk(KERN_ALERT "INVALID SPEED\n");

		period = dec * 100 / 4;
		mod_timer(&timer, jiffies + msecs_to_jiffies(period * 10));
	}
	else if (tbuf[0] == 'v' && tbuf[2] == '\0'){ // Change counter
		char n[2];
		strcpy(n, tbuf+1);
		// Check if counter w/in range, i.e. 1 to f 
		if ((n[0] >= 49 && n[0] <= 57) || (n[0] >= 97 && n[0] <= 102)){
			counter = simple_strtol(n, NULL, 16);
		}
	}
	
	(*f_pos) += count;
	return count;	
}

