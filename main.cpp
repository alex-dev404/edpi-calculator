#include <iostream>
#include <SFML/Graphics.hpp>

int dpi = 0.0f;
float sensi = 0.0f;
int edpi = 0.0f;
bool dpiInputSelected = false;
bool sensiInputSelected = false;

void calculateEDPI() {
    std::cout << "func acionada." << std::endl;
    edpi = dpi * sensi;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "EDPI_Calculator");

    sf::Font font;
    if (!font.loadFromFile("/home/alex/Área de trabalho/app dpi/Arial.ttf")) {
        std::cerr << "Erro ao carregar a fonte." << std::endl;
        return 1;
    } else {
        std::cout << "Fonte carregada com sucesso." << std::endl;
    }

    sf::Text dpiLabel("DPI DO MOUSE:", font, 20);
    sf::Text sensiLabel("SENSIBILIDADE DO JOGO:", font, 20);
    sf::Text edpiLabel("EDPI:", font, 20);
    sf::Text recomendLabel("OBS:desative a sua opcso aprimorar precisao do ponteiro \n########### RECOMENDADO ################# \nhigh sensitivity # medium sensitivity # low sensitivity \nSens: 3.09      # Sens: 2.00             # Sens: 1.51 \nDPI:  400       # DPI:  400               # DPI: 400 \neDPI: 1236    # eDPI: 800              # eDPI: 604",font, 20);
    dpiLabel.setPosition(10, 10);
    sensiLabel.setPosition(10, 50);
    edpiLabel.setPosition(10, 90);
    recomendLabel.setPosition(10, 150);

    sf::RectangleShape dpiInputBox(sf::Vector2f(280, 30));
    sf::RectangleShape sensiInputBox(sf::Vector2f(280, 30));
    sf::RectangleShape calculateButtonBox(sf::Vector2f(150, 50));
    dpiInputBox.setPosition(280, 10);
    sensiInputBox.setPosition(280, 50);
    calculateButtonBox.setPosition(375, 95);

    sf::Text dpiInput("", font, 16);
    dpiInput.setFillColor(sf::Color::Black);
    sf::Text sensiInput("", font, 16);
    sensiInput.setFillColor(sf::Color::Black);
    sf::Text edpiOutput("", font, 20);
    sf::Text calculateButtonText("Calcular", font, 32);
    calculateButtonText.setFillColor(sf::Color::Black);
    dpiInput.setPosition(280, 15);
    sensiInput.setPosition(280, 55);
    edpiOutput.setPosition(80, 90);
    calculateButtonText.setPosition(390, 98);

    while (window.isOpen()) {
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
                        dpiInputSelected = true;
                        sensiInputSelected = false;
                    }

                    // Check if the mouse is over the sensi input box
                    if (sf::Mouse::getPosition(window).x >= 280 && sf::Mouse::getPosition(window).x <= 560 &&
                        sf::Mouse::getPosition(window).y >= 50 && sf::Mouse::getPosition(window).y <= 80) {
                        dpiInputSelected = false;
                        sensiInputSelected = true;
                    }

                    // Check if the mouse is over the calculate button
                    if (sf::Mouse::getPosition(window).x >= 375 && sf::Mouse::getPosition(window).x <= 525 &&
                        sf::Mouse::getPosition(window).y >= 95 && sf::Mouse::getPosition(window).y <= 145) {
                        calculateButtonBox.setFillColor(sf::Color::Blue);
                        calculateEDPI();
                    } else {
                        calculateButtonBox.setFillColor(sf::Color::White);
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

        window.draw(dpiLabel);
        window.draw(sensiLabel);
        window.draw(edpiLabel);
        window.draw(recomendLabel);

        window.draw(dpiInputBox);
        window.draw(sensiInputBox);
        window.draw(calculateButtonBox);

        window.draw(dpiInput);
        window.draw(sensiInput);
        window.draw(edpiOutput);
        window.draw(calculateButtonText);

        window.display();
    }

    return 0;
}
