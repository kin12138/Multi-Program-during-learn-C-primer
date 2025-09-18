//
// Created by libin on 2025/6/16.
//

#ifndef ATM_INTERFACE_MACHINE_H
#define ATM_INTERFACE_MACHINE_H
#include "receiver.h"
#include "message.h"
#include "iostream"

class interface_machine {
    messaging::receiver incoming;
    std::mutex iom;
public:
    void done() {
        get_sender().send(messaging::close_queue());
    }

    void run() {
        try {
            for (;;) {
                incoming.wait()
                    .handle<issue_money>(
                            [&] (issue_money const & msg) {
                                {
                                    std::lock_guard<std::mutex> lk(iom);
                                    std::cout << "Issuing " << msg.amount << std::endl;
                                }
                            })
                    .handle<display_insufficient_funds>(
                            [&] (display_insufficient_funds const & msg) {
                                {
                                    std::lock_guard<std::mutex> lk(iom);
                                    std::cout << "Insufficient funds" << std::endl;
                                }
                            })
                    .handle<display_enter_pin>(
                            [&] (display_enter_pin const & msg) {
                                {
                                    std::lock_guard<std::mutex> lk(iom);
                                    std::cout << "Please enter your PIN (0-9)" << std::endl;
                                }
                            })
                    .handle<display_enter_card>(
                            [&] (display_enter_card const & msg) {
                                {
                                    std::lock_guard<std::mutex> lk(iom);
                                    std::cout << "Please enter your card (I)" << std::endl;
                                }
                            })
                    .handle<display_balance>(
                            [&] (display_balance const & msg) {
                                {
                                    std::lock_guard<std::mutex> lk(iom);
                                    std::cout << "The balance of your account is "
                                              << msg.amount << std::endl;
                                }
                            })
                    .handle<display_withdrawal_options>(
                            [&](display_withdrawal_options const & msg) {
                                {
                                    std::lock_guard<std::mutex> lk(iom);
                                    std::cout << "Withdraw 50 ?(w)" << std::endl;
                                    std::cout << "Display Balance? (b)" << std::endl;
                                    std::cout << "Cancel? (c)" << std::endl;
                                }
                            })
                    .handle<display_withdrawal_calcelled>(
                            [&] (display_withdrawal_calcelled const & msg) {
                                {
                                    std::lock_guard<std::mutex> lk(iom);
                                    std::cout << "Withdraw Cancelled" << std::endl;
                                }
                            })
                    .handle<display_pin_incorrect_message>(
                            [&] (display_pin_incorrect_message const & msg) {
                                {
                                    std::lock_guard<std::mutex> lk(iom);
                                    std::cout << "PIN incorrect" << std::endl;
                                }
                            })
                    .handle<eject_card>(
                            [&] (eject_card const &msg) {
                                {
                                    std::lock_guard<std::mutex> lk(iom);
                                    std::cout << "Ejecting card" << std::endl;
                                }
                            });
            }
        }
        catch (messaging::close_queue const &) {

        }
    }

    messaging::sender get_sender() {
        return incoming;
    }
};

#endif //ATM_INTERFACE_MACHINE_H
