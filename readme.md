# File Integrity Monitor (FIM)

A lightweight, secure daemon that continuously monitors file integrity using SHA-256 hashing to detect unauthorized changes in your system files.

## Overview

This File Integrity Monitor (FIM) creates and maintains cryptographic hashes of files in specified directories. By comparing current file states against a trusted baseline, it detects and alerts on unauthorized modifications, additions, or deletions—a crucial element in any cybersecurity defense strategy.

## Development Status

**Current Status: Early Development**

- ✅ SHA-256 file hashing implementation
- ✅ Hash table data structure
- ✅ Basic file reading and processing
- 🚧 Baseline creation and storage - *in progress*
- 🚧 Hash comparison logic - *in progress*
- ⏳ Daemon functionality - *planned*
- ⏳ Configuration file support - *planned*
- ⏳ Alert system - *planned*
- ⏳ Directory recursion - *planned*
- ⏳ Logging system - *planned*

This project is under active development. Contributions and suggestions are welcome!

## Features

### Core Functionality
- **SHA-256 Hashing**: Secure cryptographic hash algorithm for file content verification
- **Baseline Creation**: Establishes initial trusted state of monitored files
- **Continuous Monitoring**: Runs as a background daemon to provide real-time protection
- **Change Detection**: Identifies modifications, additions, and deletions of files

### Advanced Features
- **Alerting System**: Configurable notifications for detected changes
- **Persistence**: Stores hash database between system restarts
- **Recursive Directory Monitoring**: Monitors entire directory trees
- **Exclusion Rules**: Configurable paths and patterns to exclude from monitoring
- **Performance Optimization**: Smart scanning to minimize system impact
- **Detailed Logging**: Comprehensive event recording for forensic analysis

## Technical Implementation

- **Daemon Process**: Runs continuously in the background with minimal resource usage
- **Hash Table**: Efficient storage and lookup of file hashes
- **OpenSSL Integration**: Uses industry-standard cryptographic libraries for SHA-256 implementation
- **Signal Handling**: Graceful startup, shutdown, and configuration reloading

## Usage

### Installation

```bash
git clone https://github.com/9nickss/File_Integrity_Monitor.git
cd File_Integrity_Monitor
make
```

### Basic Commands

```bash
# Start monitoring with default configuration
./fim start

# Establish a new baseline for monitored files
./fim baseline

# Check current status of monitored files
./fim check

# Stop the monitoring daemon
./fim stop
```

### Configuration

The FIM can be configured by editing the `fim.conf` file:

# Directories to monitor
monitor_dir=/etc
monitor_dir=/usr/bin
monitor_dir=/boot

# Directories/patterns to exclude
exclude=*.log
exclude=/var/tmp

# Scanning frequency (in seconds)
interval=300

# Alert settings
alert_method=email
alert_recipient=admin@example.com


Requirements
C compiler (GCC/Clang)
OpenSSL development libraries
Linux-based operating system
License
This project is licensed under the MIT License - see the LICENSE file for details.

Author
9nickss (2025) ```