import udp as dp

while True:
   str = dp.udp_read("192.168.1.50",5050)
   print(str)

   