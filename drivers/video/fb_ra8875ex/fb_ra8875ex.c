#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/spi/spi.h>

#define DRVNAME "fb_ra8875ex"

struct spi_device *spi_device;
struct platform_device *p_device;

static const struct of_device_id dt_ids[] = {
        { .compatible = "raio,ra8875ex" },
        {},
};
static void device_spi_delete(struct spi_master *master, unsigned cs)
{
	struct device *dev;
	char str[32];

	snprintf(str, sizeof(str), "%s.%u", dev_name(&master->dev), cs);

	dev = bus_find_device_by_name(&spi_bus_type, NULL, str);
	if (dev) {
		if (verbose)
			pr_info(DRVNAME": Deleting %s\n", str);
		device_del(dev);
	}
}
static int device_spi_register(struct spi_board_info *spi)
{
	struct spi_master *master;

	master = spi_busnum_to_master(spi->bus_num);
	if (!master) {
		pr_err(DRVNAME ":  spi_busnum_to_master(%d) returned NULL\n",
								spi->bus_num);
		return -EINVAL;
	}
	/* make sure it's available */
	fbtft_device_spi_delete(master, spi->chip_select);
	spi_device = spi_new_device(master, spi);
	put_device(&master->dev);
	if (!spi_device) {
		pr_err(DRVNAME ":    spi_new_device() returned NULL\n");
		return -EPERM;
	}
	return 0;
}

static int __init fbd_init(void)
{
    struct spi_board_info spi
	pr_debug("\n\n"DRVNAME": init\n");

	struct spi_master *master;
    master = spi_busnum_to_master(spiBus);
    if (!master) {
		pr_err(DRVNAME ":  spi_busnum_to_master(%d) returned NULL\n", spiBus);
		return -EINVAL;
	}
    spi_device = spi_new_device(master, spi);
    return 0;
}
static void __exit fbd_exit(void)
{
    pr_alert("ra8875ex exit\n");
}

module_init(fbd_init);
module_exit(fbd_exit);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:ra8875ex");
MODULE_ALIAS("platform:ra8875ex");
MODULE_DESCRIPTION("Standalone FB driver for the RA8875 LCD Controller");
MODULE_AUTHOR("oleg.v.lytvynenko@gmail.com");
MODULE_LICENSE("GPL");
