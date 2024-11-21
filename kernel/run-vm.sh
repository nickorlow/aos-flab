qemu-system-x86_64 \
    -enable-kvm \
    -m 8096 \
    -smp cpus=4,cores=4 \
    -cpu host \
    -nic user,model=virtio,hostfwd=tcp::2222-:22 \
    -kernel /home/nickorlow/programming/school/aos-flab/kernel/build/arch/x86_64/boot/bzImage \
    -nographic \
    -drive file=$1,media=disk,if=virtio \
    -monitor telnet:127.0.0.1:55555,server,nowait \
    -append "root=/dev/vda1 console=ttyS0,115200n8 pti=yes nokasrl" \
    -virtfs local,path=/home/nickorlow/programming/school/aos-lab2/,mount_tag=host1,security_model=passthrough,id=host0 \
    -s