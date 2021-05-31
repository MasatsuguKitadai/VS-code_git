import time

start = time.time()

while True:

    rap_start = time.time()
    time.sleep(2)
    total_time = time.time() - start
    print(total_time)

    if total_time > 20:
        break
