#!/usr/bin/env python

import time
import psutil

if __name__ == "__main__":
	while True:
		print psutil.cpu_percent(percpu = True)
		time.sleep(1)
