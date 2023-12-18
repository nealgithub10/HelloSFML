//
// Created by Neal Rangarajan on 12/5/23.
//

#include <openai.hpp>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>  // nlohmann/json

using Json = nlohmann::json;

//std::string showcase(std::string transcript2) {
int main() {
//    openai::start(); // Will use the api key provided by `OPENAI_API_KEY` environment variable
//    // openai::start("your_API_key", "optional_organization"); // Or you can handle it yourself

    openai::start("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");
    std::string transcript = "Summarize the following text into 6 sentences";
    Json jsonData = {
            {"model", "text-davinci-003"},
            {"prompt", transcript},
            {"max_tokens", 7},
            {"temperature", 0}
    };
    auto completion = openai::completion().create(jsonData);

    std::cout << "Response is:\n" << completion.dump(2) << '\n';

    return 0;
}

