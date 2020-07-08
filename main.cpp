#include <fmt/core.h>
#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <fstream>
#include <list>
#include <sstream>

std::string get_extension(std::string content_type) {
    content_type = content_type.substr(0, content_type.find(';'));
    std::string file_extension = content_type.substr(content_type.find('/') + 1, content_type.size());
    return file_extension;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "[ERROR] Usage: fetcher url" << std::endl;
        return 0;
    }

    try {
        /*That's all that is needed to do cleanup of used resources (RAII style)*/
        curlpp::Cleanup cleaner;

        /*Our request to be sent*/
        curlpp::Easy request;

        /*Set options*/
        request.setOpt<curlpp::options::Url>(argv[1]);
        request.setOpt<curlpp::options::CaInfo>("cacert.pem");
        request.setOpt<curlpp::options::FollowLocation>(true);
        request.setOpt<curlpp::options::UserAgent>("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.116 Safari/537.36 Edg/83.0.478.58");
        // request.setOpt<curlpp::options::Verbose>(true);
        request.setOpt<curlpp::options::ForbidReuse>(true);

        // std::list<std::string> headers;
        // headers.push_back("Connection: close");
        // request.setOpt<curlpp::options::HttpHeader>(headers);

        std::ostringstream os;
        curlpp::options::WriteStream ws(&os);
        request.setOpt(ws);

        /*Send request and get a result*/
        request.perform();

        std::string file_extension = get_extension(curlpp::infos::ContentType::get(request));
        std::string file_name = fmt::format("index.{}", file_extension);

        std::ofstream file;
        file.open(file_name, std::ofstream::binary);
        file << os.str();
        file.close();

        // Debugging code
        // std::cout << "\n\nResponse Code: " << curlpp::infos::ResponseCode::get(request) << std::endl;
        // std::cout << "\n\nResponse Code: " << curlpp::infos::EffectiveUrl::get(request) << std::endl;

    } catch (curlpp::RuntimeError& e) {
        std::cout << e.what() << std::endl;
    } catch (curlpp::LogicError& e) {
        std::cout << e.what() << std::endl;
    }
}
