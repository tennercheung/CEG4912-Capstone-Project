import spidev
import time

# Initialize SPI
spi = spidev.SpiDev()
spi.open(0,0)  # Open SPI bus 0, device 0
spi.max_speed_hz = 500000  # Set SPI speed (max speed may vary depending on your setup)
spi.mode = 0b00  # Set SPI mode (mode 0 recommended for most devices)

# # Function to write data to SD card
# def write_to_sdcard(data):
#     spi.xfer2(data)  # Send data to SD card

# Function to read content from data.txt on SD card
def read_from_sdcard():
    try:
        # Open the data.txt file for reading
        with open('/data.txt', 'r', encoding='utf-8') as file:
            # Read the content of the file
            content = file.read()
            data_read = [ord(char) for char in content]
            return data_read
    except FileNotFoundError:
        print("data.txt file not found on the SD card.")
        return []
    except Exception as e:
        print("An error occurred while reading data.txt:", e)
        return []

# Function to write string to data.txt on SD card
def write_string_to_file(string):
    with open('/data.txt', 'w', encoding='utf-8') as file:
        file.write(string)
        file.flush()

# Example string to write to SD card
string_to_write = "plastic"
# str_2 = "glass"
# Convert string to bytes
data_to_write = [ord(char) for char in string_to_write]




# # Write data to SD card
# write_to_sdcard(data_to_write)

# Wait for a moment before reading (optional)
time.sleep(0.5)

# Read data from SD card
data_read = read_from_sdcard()

# Convert bytes back to string
string_read = ''.join(chr(byte) for byte in data_read)

print("Found on SD: "+string_read)

# Write or overwrite string to data.txt on SD card
write_string_to_file(string_to_write)

print("Wrote: "+string_to_write)


# # Wait for a moment before reading (optional)
# time.sleep(0.5)

# # Read data from SD card
# data_read = read_from_sdcard()

# # Convert bytes back to string
# string_read = ''.join(chr(byte) for byte in data_read)

# print("Found on SD: "+string_read)

# # Write or overwrite string to data.txt on SD card
# write_string_to_file(str_2)

# print("Wrote: "+str_2)





# Close SPI connection
spi.close()
