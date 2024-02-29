#include <iostream>
#include <SFML/Graphics.hpp>

int dpi = 0;
float sensi = 0.0f;
int edpi = 0;
bool dpiInputSelected = false;
bool sensiInputSelected = false;
int menu = 1;
sf::RenderWindow window(sf::VideoMode(600, 400), "EDPI_Calculator");
sf::Vector2i initialMousePos = sf::Mouse::getPosition();

void calculateEDPI() {
    std::cout << "func acionada." << std::endl;
    edpi = dpi * sensi;
}

void calculateSensi(){
     if (dpi != 0) {
        sensi = static_cast<float>(edpi) / dpi;
    } else {
        std::cerr << "Erro: DPI não pode ser zero." << std::endl;
    }
}

void draw_menu1(){
    sf::Font font;
    if (!font.loadFromFile("Creepster-Regular.ttf")) {
        std::cerr << "Erro ao carregar a fonte." << std::endl;
    } else {
        std::cout << "Fonte carregada com sucesso." << std::endl;
    }
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.jpg")) {
    }
    sf::Sprite backgroundImage(backgroundTexture);
    sf::Text dpiLabel("DPI DO MOUSE:", font, 20);
    sf::Text sensiLabel("SENSIBILIDADE DO JOGO:", font, 20);
    sf::Text edpiLabel("EDPI:", font, 20);
    dpiLabel.setPosition(10, 10);
    sensiLabel.setPosition(10, 50);
    edpiLabel.setPosition(10, 90);


    sf::RectangleShape dpiInputBox(sf::Vector2f(280, 30));
    sf::RectangleShape sensiInputBox(sf::Vector2f(280, 30));
    sf::RectangleShape calculateButtonBox(sf::Vector2f(120, 30));
    sf::RectangleShape sensiButtonBox(sf::Vector2f(120, 30));
    dpiInputBox.setPosition(280, 10);
    sensiInputBox.setPosition(280, 50);
    calculateButtonBox.setPosition(440, 90);
    sensiButtonBox.setPosition(280, 90);

    sf::Text dpiInput("", font, 16);
    dpiInput.setFillColor(sf::Color::Black);
    sf::Text sensiInput("", font, 16);
    sensiInput.setFillColor(sf::Color::Black);
    sf::Text edpiOutput("", font, 20);
    sf::Text calculateButtonText("Calcular", font, 30);
    calculateButtonText.setFillColor(sf::Color::Black);
    sf::Text sensibuton("SENSI?", font, 30);
    sensibuton.setFillColor(sf::Color::Black);
    dpiInput.setPosition(280, 15);
    sensiInput.setPosition(280, 55);
    edpiOutput.setPosition(80, 90);
    calculateButtonText.setPosition(448, 88);
    sensibuton.setPosition(298,88);

    while (window.isOpen() && menu == 1) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if the mouse is over the dpi input box
                    if (sf::Mouse::getPosition(window).x >= 280 && sf::Mouse::getPosition(window).x <= 560 &&
                        sf::Mouse::getPosition(window).y >= 10 && sf::Mouse::getPosition(window).y <= 40) {
                        dpiInputBox.setFillColor(sf::Color::Cyan);
                        sensiInputBox.setFillColor(sf::Color::White);
                        dpiInputSelected = true;
                        sensiInputSelected = false;
                    }

                    // Check if the mouse is over the sensi input box
                    if (sf::Mouse::getPosition(window).x >= 280 && sf::Mouse::getPosition(window).x <= 560 &&
                        sf::Mouse::getPosition(window).y >= 50 && sf::Mouse::getPosition(window).y <= 80) {
                        sensiInputBox.setFillColor(sf::Color::Cyan);
                        dpiInputBox.setFillColor(sf::Color::White);
                        dpiInputSelected = false;
                        sensiInputSelected = true;
                    }

                    // Check if the mouse is over the calculate button
                    if (sf::Mouse::getPosition(window).x >= 440 && sf::Mouse::getPosition(window).x <= 560 &&
                        sf::Mouse::getPosition(window).y >= 90 && sf::Mouse::getPosition(window).y <= 120) {
                        calculateButtonBox.setFillColor(sf::Color::Blue);
                        calculateEDPI();
                    } else {
                        calculateButtonBox.setFillColor(sf::Color::White);
                    }
                    // check if the mouse is over the button sensi
                    if (sf::Mouse::getPosition(window).x >= 280 && sf::Mouse::getPosition(window).x <= 400 &&
                        sf::Mouse::getPosition(window).y >= 90 && sf::Mouse::getPosition(window).y <= 120) {
                        sensiButtonBox.setFillColor(sf::Color::Blue);
                        menu = 2;
                    } else {
                        sensiButtonBox.setFillColor(sf::Color::White);
                    }
                }
            }

            // Handle input events
            if (event.type == sf::Event::TextEntered) {
                if (dpiInputSelected || sensiInputSelected) {
                    // Handle DPI and Sensi input
                    if (event.text.unicode >= 48 && event.text.unicode <= 57) {
                        sf::Text* activeInput = (dpiInputSelected) ? &dpiInput : &sensiInput;

                        if (activeInput->getString().getSize() < 4) {
                            activeInput->setString(activeInput->getString() + static_cast<char>(event.text.unicode));

                            if (dpiInputSelected) {
                                dpi = std::stoi(dpiInput.getString().toAnsiString());
                            } else {
                                sensi = std::stof(sensiInput.getString().toAnsiString());
                            }
                        }
                    } else if (event.text.unicode == 46) {  // Handle decimal point for sensi
                        if (!sensiInput.getString().isEmpty() && sensiInput.getString().find('.') == sf::String::InvalidPos) {
                            sensiInput.setString(sensiInput.getString() + ".");
                            sensi = std::stof(sensiInput.getString().toAnsiString());
                        }
                    } else if (event.text.unicode == 8) {  // Backspace
                        sf::Text* activeInput = (dpiInputSelected) ? &dpiInput : &sensiInput;

                        if (!activeInput->getString().isEmpty()) {
                            activeInput->setString(activeInput->getString().substring(0, activeInput->getString().getSize() - 1));

                            if (dpiInputSelected) {
                                dpi = (dpiInput.getString().isEmpty()) ? 0 : std::stoi(dpiInput.getString().toAnsiString());
                            } else {
                                sensi = (sensiInput.getString().isEmpty()) ? 0.0f : std::stof(sensiInput.getString().toAnsiString());
                            }
                        }
                    }
                }
            }
        }
        dpiInput.setString(std::to_string(dpi));
        edpiOutput.setString(std::to_string(edpi));

        window.clear(sf::Color::Black);
        window.draw(backgroundImage);
        window.draw(dpiLabel);
        window.draw(sensiLabel);
        window.draw(edpiLabel);

        window.draw(dpiInputBox);
        window.draw(sensiInputBox);
        window.draw(calculateButtonBox);
        window.draw(sensiButtonBox);

        window.draw(dpiInput);
        window.draw(sensiInput);
        window.draw(edpiOutput);
        window.draw(calculateButtonText);
        window.draw(sensibuton);

        window.display();
    }
}
void draw_menu2(){
    sf::Font font;
    if (!font.loadFromFile("Creepster-Regular.ttf")) {
        std::cerr << "Erro ao carregar a fonte." << std::endl;
    } else {
        std::cout << "Fonte carregada com sucesso." << std::endl;
    }
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.jpg")) {
    }
    sf::Sprite backgroundImage(backgroundTexture);
    sf::Text dpiLabel("DPI DO MOUSE:", font, 20);
    sf::Text sensiLabel("EDPI DO JOGADOR:", font, 20);
    sf::Text edpiLabel("SENSI:", font, 20);
    dpiLabel.setPosition(10, 10);
    sensiLabel.setPosition(10, 50);
    edpiLabel.setPosition(10, 90);


    sf::RectangleShape dpiInputBox(sf::Vector2f(280, 30));
    sf::RectangleShape sensiInputBox(sf::Vector2f(280, 30));
    sf::RectangleShape calculateButtonBox(sf::Vector2f(120, 30));
    sf::RectangleShape edpiButtonBox(sf::Vector2f(120, 30));
    dpiInputBox.setPosition(280, 10);
    sensiInputBox.setPosition(280, 50);
    calculateButtonBox.setPosition(440, 90);
    edpiButtonBox.setPosition(280, 90);

    sf::Text dpiInput("", font, 16);
    dpiInput.setFillColor(sf::Color::Black);
    sf::Text sensiInput("", font, 16);
    sensiInput.setFillColor(sf::Color::Black);
    sf::Text edpiOutput("", font, 20);
    sf::Text calculateButtonText("Calcular", font, 30);
    calculateButtonText.setFillColor(sf::Color::Black);
    sf::Text edpibutomtext("EDPI?", font, 30);
    edpibutomtext.setFillColor(sf::Color::Black);
    dpiInput.setPosition(280, 15);
    sensiInput.setPosition(280, 55);
    edpiOutput.setPosition(80, 90);
    calculateButtonText.setPosition(448, 88);
    edpibutomtext.setPosition(305,88);


    while (window.isOpen() && menu == 2) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if the mouse is over the dpi input box
                    if (sf::Mouse::getPosition(window).x >= 280 && sf::Mouse::getPosition(window).x <= 560 &&
                        sf::Mouse::getPosition(window).y >= 10 && sf::Mouse::getPosition(window).y <= 40) {
                        dpiInputBox.setFillColor(sf::Color::Cyan);
                        sensiInputBox.setFillColor(sf::Color::White);
                        dpiInputSelected = true;
                        sensiInputSelected = false;
                    }

                    // Check if the mouse is over the sensi input box
                    if (sf::Mouse::getPosition(window).x >= 280 && sf::Mouse::getPosition(window).x <= 560 &&
                        sf::Mouse::getPosition(window).y >= 50 && sf::Mouse::getPosition(window).y <= 80) {
                        sensiInputBox.setFillColor(sf::Color::Cyan);
                        dpiInputBox.setFillColor(sf::Color::White);
                        dpiInputSelected = false;
                        sensiInputSelected = true;
                    }

                    // Check if the mouse is over the calculate button
                    if (sf::Mouse::getPosition(window).x >= 440 && sf::Mouse::getPosition(window).x <= 560 &&
                        sf::Mouse::getPosition(window).y >= 90 && sf::Mouse::getPosition(window).y <= 120) {
                        calculateButtonBox.setFillColor(sf::Color::Blue);
                        calculateSensi();
                    } else {
                        calculateButtonBox.setFillColor(sf::Color::White);
                    }
                    // check if the mouse is over the button edpi
                    if (sf::Mouse::getPosition(window).x >= 280 && sf::Mouse::getPosition(window).x <= 400 &&
                        sf::Mouse::getPosition(window).y >= 90 && sf::Mouse::getPosition(window).y <= 120) {
                        edpiButtonBox.setFillColor(sf::Color::Blue);
                        menu = 1;
                    } else {
                        edpiButtonBox.setFillColor(sf::Color::White);
                    }
                }
            }

            // Handle input events
            if (event.type == sf::Event::TextEntered) {
                if (dpiInputSelected || sensiInputSelected) {
                    // Handle DPI and Sensi input
                    if (event.text.unicode >= 48 && event.text.unicode <= 57) {
                        sf::Text* activeInput = (dpiInputSelected) ? &dpiInput : &sensiInput;

                        if (activeInput->getString().getSize() < 4) {
                            activeInput->setString(activeInput->getString() + static_cast<char>(event.text.unicode));

                            if (dpiInputSelected) {
                                dpi = std::stoi(dpiInput.getString().toAnsiString());
                            } else {
                                edpi = std::stoi(sensiInput.getString().toAnsiString());
                            }
                        }
                    } else if (event.text.unicode == 46) {  // Handle decimal point for sensi
                        if (!sensiInput.getString().isEmpty() && sensiInput.getString().find('.') == sf::String::InvalidPos) {
                            sensiInput.setString(sensiInput.getString() + ".");
                            edpi = std::stoi(sensiInput.getString().toAnsiString());
                        }
                    } else if (event.text.unicode == 8) {  // Backspace
                        sf::Text* activeInput = (dpiInputSelected) ? &dpiInput : &sensiInput;

                        if (!activeInput->getString().isEmpty()) {
                            activeInput->setString(activeInput->getString().substring(0, activeInput->getString().getSize() - 1));

                            if (dpiInputSelected) {
                                dpi = (dpiInput.getString().isEmpty()) ? 0 : std::stoi(dpiInput.getString().toAnsiString());
                            } else {
                                edpi = (sensiInput.getString().isEmpty()) ? 0: std::stoi(sensiInput.getString().toAnsiString());
                            }
                        }
                    }
                }
            }
        }
        dpiInput.setString(std::to_string(dpi));
        edpiOutput.setString(std::to_string(sensi));
        window.clear(sf::Color::Black);
        window.draw(backgroundImage);
        window.draw(dpiLabel);
        window.draw(sensiLabel);
        window.draw(edpiLabel);

        window.draw(dpiInputBox);
        window.draw(sensiInputBox);
        window.draw(calculateButtonBox);
        window.draw(edpiButtonBox);

        window.draw(dpiInput);
        window.draw(sensiInput);
        window.draw(edpiOutput);
        window.draw(calculateButtonText);
        window.draw(edpibutomtext);

        window.display();
    }
}

int main() {
    while (window.isOpen()) {
        if (menu == 1) {
            dpi =0;
            edpi= 0;
            sensi=0.0;
            draw_menu1();
        } else if (menu == 2) {
            dpi =0;
            edpi= 0;
            sensi=0.0;
            draw_menu2();
        }
    }

    return 0;
}

