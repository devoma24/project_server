#include "../include/Server.h"
//#include "ThreadPool.h"
#include <iostream>


/*int main() {
    ThreadPool pool(1);

    for (int i = 0; i < 5; ++i) {
        pool.submit([i] {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Task " << i << " done\n";
        });
    }
}*/


int main()
{
    try
    {
        Server server(8080, 4);
        server.start();

        std::cout << "Press Enter to stop server...\n";
        std::cin.get();

        server.stop();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}