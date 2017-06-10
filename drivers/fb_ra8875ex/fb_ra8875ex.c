#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/spi/spi.h>

static const struct of_device_id dt_ids[] = {
        { .compatible = "raio,ra8875ex" },
        {},
};
static int __init fbd_init(void)
{
    pr_alert("ra8875ex init\n");
    return 0;
}
static void __exit fbd_exit(void)
{
    pr_alert("ra8875ex exit\n");
}
module_init(fbd_init);
module_exit(fbd_exit);	

MODULE_DESCRIPTION("Standalone FB driver for the RA8875 LCD Controller");
MODULE_AUTHOR("oleg.v.lytvynenko@gmail.com");
MODULE_LICENSE("GPL");
