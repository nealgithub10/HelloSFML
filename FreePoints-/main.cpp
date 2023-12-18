#include <SFML/Graphics.hpp>
#include <iostream>  // Include this for cout
#include <curl/curl.h>
#include "TextBox.h"
#include "Button.h"
#include "TranscriptStealer.h"
#include "include/openai/openai.hpp"
#include <string>
#include "include/openai/nlohmann/json.hpp"

using Json = nlohmann::json;

std::string summarize_GPT(std::string transcript) {
//    openai::start(); // Will use the api key provided by `OPENAI_API_KEY` environment variable
//    // openai::start("your_API_key", "optional_organization"); // Or you can handle it yourself

    std::cout << transcript << std::endl;
    openai::start("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");
    std::string prompt = "Summarize: " + transcript;
    Json jsonData = {
            {"model", "text-davinci-003"},
            {"prompt", prompt},
            {"max_tokens", 1000},
            {"temperature", 0}
    };
    auto completion = openai::completion().create(jsonData);
    //std::string output = completion.dump(2);

    //std::cout << completion.at("choices") << std::endl;
    std::string output_text = completion["choices"][0]["text"].dump();


    return output_text;
}

std::string wrapText(const std::string& text, float wrapWidth, sf::Font& font, int charSize) {
    std::string wrappedText;
    float lineWidth = 0.f;

    for (char c : text) {
        float charWidth = font.getGlyph(c, charSize,true).bounds.width;

        if (lineWidth + charWidth > wrapWidth) {
            wrappedText += '\n';
            lineWidth = charWidth;
        } else {
            lineWidth += charWidth;
            wrappedText += c;
        }
    }

    return wrappedText;
}
int main() {
    //creates the window + add the font
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "YouTube++");
    sf::Font font;
    if (!font.loadFromFile("/Users/nealrangarajan/Downloads/Inter/static/Inter-Bold.ttf"))
    {
        std::cout << "font unable to load" << std::endl;
    }


    //main text box to add code
    Textbox text(20, sf::Color::Black, true);
    text.setPosition({ 700, 300 });
    text.setLimit(true, 30);
    text.setFont(font);



    //btn to enter code
    Button btn1("Enter", { 200, 100 }, 30, sf::Color::Red, sf::Color::Black);
    btn1.setFont(font);
    btn1.setPosition({ 700, 500 });


    //string for input:
    sf::String playerInput;
    sf::String transcript;


    //image on app
    sf::Image pic;
    pic.loadFromFile("/Users/nealrangarajan/Downloads/logo.png");
    sf::Texture texture;
    texture.loadFromImage(pic);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.5,0.5);
    sprite.setPosition(250,0);

    //icon for app
    sf::Image icon;
    icon.loadFromFile("/Users/nealrangarajan/Downloads/logo.png");

    //some text for the headder
    sf::Text inputBox;
    inputBox.setFont(font);
    inputBox.setPosition(500, 10);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setString("Welcome to the Youtube Transcript Generator");


    sf::Text outputBox;
    outputBox.setFont(font);
    outputBox.setPosition(400, 300);
    outputBox.setOutlineThickness(2);
    outputBox.setOutlineColor(sf::Color::Black);
    outputBox.setCharacterSize(15);




    while (window.isOpen()) {
        //the basic event used for checking what's gonna happen
        sf::Event event;

        //Just checks if the keyboard is being used with a return key click
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            text.setSelected(true);
        }
        //gets rid of the typing feature
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            text.setSelected(false);
        }
        while (window.pollEvent(event))
        {
            //window actions
            if (event.type == sf::Event::Closed)
                window.close();

            //basic typing function
           if (event.type == sf::Event::TextEntered) {
               std::cout << "Text being entered." << std::endl;
               text.typedOn(event);
           }

           //basic button action
            if (event.type == sf::Event::MouseMoved) {
                if (btn1.isMouseOver(window)) {

                    sf::Color button_color(211,211,211);
                    btn1.setBackColor(button_color);
                } else {
                    btn1.setBackColor(sf::Color::Red);

            }
        }
            //this actually updates the text.
            text.palette(event);

            //the transcript stealer function
            if(event.type == sf::Event::MouseButtonPressed) {
                std::string url = text.getText();
                TranscriptStealer stealer;
                std::cout << url << std::endl;
                std::string trans = stealer.getTranscript(url);

                outputBox.setFont(font);
                std::cout << trans << std::endl;
                std::string summary = summarize_GPT(trans);
                outputBox.setString(wrapText(summary, window.getSize().x - 20, font, 20));
                //outputBox(wrapText(trans, window.getSize().x - 20, font, 20), font);


                //outputBox.setString(trans);
            }
        }

        window.setIcon(960,720,icon.getPixelsPtr());

        window.clear(sf::Color::White);
       // window.draw(inputText);
        window.draw(inputBox);
        window.draw(outputBox);
       // window.draw(sprite);
        btn1.drawTo(window);

        text.drawTo(window);


        // window.draw(summaryText);
        window.display();
    }

    return 0;
}
