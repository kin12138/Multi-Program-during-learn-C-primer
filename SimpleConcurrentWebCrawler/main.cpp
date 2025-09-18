#include "CrawlerController.h"

int main() {
    CrawlerController crawler(2, 4);
    crawler.addSeed("https://cppreference.com");
    crawler.start();            // 启动主循环：读取队列并分发任务
    crawler.waitFinsh();        // 关闭队列，并等待线程池析构
    return 0;
}
