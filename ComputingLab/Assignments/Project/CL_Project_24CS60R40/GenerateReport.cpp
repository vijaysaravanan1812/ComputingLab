
#include <iostream>
#include <sys/sysinfo.h>
#include <chrono>
#include <thread>
#include <fstream>  
#include <sstream>  

// Function to get memory utilization percentage
double getMemoryUtilization() {
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        std::cerr << "sysinfo() failed to retrieve memory info." << std::endl;
        return -1;
    }

    // Calculate memory usage as a percentage
    double totalMemory = info.totalram;
    double freeMemory = info.freeram;
    double usedMemory = totalMemory - freeMemory;

    return (usedMemory / totalMemory) * 100.0;
}

// Function to get CPU utilization over a short interval
double getCpuUtilization() {
    static long prevIdle = 0, prevTotal = 0;
    long idle, total;
    std::ifstream proc_stat("/proc/stat");

    if (!proc_stat.is_open()) {
        std::cerr << "Failed to open /proc/stat" << std::endl;
        return -1;
    }

    std::string line, cpu;
    long user, nice, system, idleTime, iowait, irq, softirq, steal;

    std::getline(proc_stat, line);
    std::istringstream ss(line);
    ss >> cpu >> user >> nice >> system >> idleTime >> iowait >> irq >> softirq >> steal;
    proc_stat.close();

    idle = idleTime + iowait;
    total = user + nice + system + idle + irq + softirq + steal;

    long idleDiff = idle - prevIdle;
    long totalDiff = total - prevTotal;

    prevIdle = idle;
    prevTotal = total;

    return 100.0 * (1.0 - static_cast<double>(idleDiff) / totalDiff);
}

int main() {
    while (true) {
        // Get memory utilization
        double memoryUtilization = getMemoryUtilization();
        if (memoryUtilization != -1) {
            std::cout << "Memory Utilization: " << memoryUtilization << "%" << std::endl;
        }

        // Get CPU utilization
        double cpuUtilization = getCpuUtilization();
        if (cpuUtilization != -1) {
            std::cout << "CPU Utilization: " << cpuUtilization << "%" << std::endl;
        }

        // Pause for a short interval (1 second)
         std::this_thread::sleep_for(std::chrono::seconds(1));
      
    }
     
    return 0;
}


            