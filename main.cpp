#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Infos.hpp>

using namespace curlpp::options;

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "[ERROR] Usage: fetcher url" << std::endl;
        return 0;
    }

    try {
        /*That's all that is needed to do cleanup of used resources (RAII style)*/
        curlpp::Cleanup myCleanup;

        /*Our request to be sent*/
        curlpp::Easy myRequest;

        /*Set the URL*/
        myRequest.setOpt<Url>(argv[1]);
        myRequest.setOpt<CaInfo>("cacert.pem");
        myRequest.setOpt<FollowLocation>(true);

        /*Send request and get a result*/
        /*By default the result goes to standard output*/
        myRequest.perform();

        /*Debugging code*/
        //std::cout << "\n\nResponse Code: " << curlpp::infos::ResponseCode::get(myRequest) << std::endl;

    } catch (curlpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    } catch (curlpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
