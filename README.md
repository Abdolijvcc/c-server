# c-server

![C](https://img.shields.io/badge/language-C-blue)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey)
![Status](https://img.shields.io/badge/status-in%20development-yellow)
![License](https://img.shields.io/badge/license-MIT-green)

Simple and fast video processing pipeline in C using HandBrakeCLI.

---

## Features

- Recursive directory scanning  
- Automatic video file detection  
- Queue-based processing system  
- HandBrakeCLI command generation and execution  
- Prepared for real-time file watching (work in progress)  
- Modular architecture in pure C  

---

## Project Structure

```

proyecto/
│
├── main.c
├── scanner.c / scanner.h
├── filter.c / filter.h
├── queue.c / queue.h
├── worker.c / worker.h
├── watcher.c / watcher.h
├── platform.c / platform.h
├── HandBrakeCLI_confg.c / .h
│
├── bin/
│   └── HandBrakeCLI.exe
│
└── README.md

````

---

## How It Works

1. Scans a root directory recursively  
2. Detects valid video files (e.g. .mp4)  
3. Adds them to a processing queue  
4. Builds a HandBrakeCLI command  
5. Executes encoding  

---

## Encoding Configuration

Optimized for balanced quality and size:

- Codec: x265 (H.265)  
- Quality: -q 26  
- Encoder preset: slow  
- Framerate: --vfr  
- Audio: 96 kbps  
- Audio codec: AAC  
- Resolution: original (no forced downscale)  

### Example command

```bash
HandBrakeCLI.exe -i "input.mp4" -o "output.mp4" \
-e x265 -q 26 --encoder-preset slow \
--vfr -B 96 -E av_aac
````

---

## Example Output

```
Scanning initial folder...
Input: C:\Videos\file.mp4
 -> valid file

Processing queue...

[INFO] Encoding started...
[INFO] Encoding finished successfully
```

---

## Build

```bash
gcc -Wall -Wextra -pedantic main.c platform.c scanner.c queue.c filter.c worker.c watcher.c HandBrakeCLI_confg.c -o a.exe
```

---

## Run

```bash
./a.exe
```

---

## Notes

Lower -q means higher quality and larger file size.
Higher -q means lower quality and smaller file size.

| Quality | Result                 |
| ------- | ---------------------- |
| -q 24   | High quality           |
| -q 26   | Balanced               |
| -q 28+  | Aggressive compression |

---

## Roadmap

* [ ] Real-time folder watcher
* [ ] Automatic output folder creation
* [ ] Improved error handling
* [ ] Config file support
* [ ] Parallel processing

---

## Contributing

Pull requests are welcome. For major changes, open an issue first.

---

