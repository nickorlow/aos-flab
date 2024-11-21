build:
	gcc test.c -o test

transfer: build
	sudo mkdir -p /mnt/  && \
	sudo mkdir -p /mnt/vm_kernel/ && \
 	sudo guestmount /mnt/vm_kernel -a ../debian-12-nocloud-amd64-20240901-1857.qcow2 -i && \
	sudo cp test /mnt/vm_kernel/root
	sudo guestunmount /mnt/vm_kernel
