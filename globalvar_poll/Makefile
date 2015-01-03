obj-m=globalvar_poll$(num).o
KERNELDIR=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)
modules:
	KCPPFLAGS="-DDEVICE_NUM=$(num)" $(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers *.order
