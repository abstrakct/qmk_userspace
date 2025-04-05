#!/bin/sh

# Function to mount the keyboard storage
mount_keyboard() {
    while true; do
        if sudo mount /dev/sde1 /mnt/kb; then
            echo "Successfully mounted keyboard"
            return 0
        else
            echo "Failed to mount keyboard, retrying in 1 second..."
            sleep 1
        fi
    done
}

# Mount the keyboard with retry logic
mount_keyboard

# Copy the firmware
sudo cp silakka54_abstrakct.uf2 /mnt/kb/

# Unmount the keyboard storage
sudo umount /dev/sde1
