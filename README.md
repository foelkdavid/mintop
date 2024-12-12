# mintop
tiny system usage monitor providing system usage stats in json format.


## Example output
```bash
{
  "cpu_usage_percent": 6.08,
  "cpu_temp_celsius": 53,
  "ram_usage_percent": 50.09,
  "load_average": {
    "1min_percent": 0.47,
    "5min_percent": 0.57,
    "15min_percent": 0.46
  "disk": {
    "rootfs_total_gb": 394,
    "rootfs_used_gb": 218,
    "rootfs_usage_percent": 55
  }
}
```

## building
right now the makefile just supports `zig cc` but its very easy to use the compiler of your choice.

> just use the compiler of your choice.
