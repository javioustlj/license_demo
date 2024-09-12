#include "license_demo.h"

int check_license(void)
{
    std::unordered_map<LCC_EVENT_TYPE, std::string> stringByEventType = {
        {LICENSE_OK, "OK "},
        {LICENSE_FILE_NOT_FOUND, "license file not found "},
        {LICENSE_SERVER_NOT_FOUND, "license server can't be contacted "},
        {ENVIRONMENT_VARIABLE_NOT_DEFINED, "environment variable not defined "},
        {FILE_FORMAT_NOT_RECOGNIZED, "license file has invalid format (not .ini file) "},
        {LICENSE_MALFORMED, "some mandatory field are missing, or data can't be fully read. "},
        {PRODUCT_NOT_LICENSED, "this product was not licensed "},
        {PRODUCT_EXPIRED, "license expired "},
        {LICENSE_CORRUPTED, "license signature didn't match with current license "},
        {IDENTIFIERS_MISMATCH, "Calculated identifier and the one provided in license didn't match"}};

    LicenseInfo licenseInfo;

    LCC_EVENT_TYPE result = acquire_license(nullptr, nullptr, &licenseInfo);

    if (result == LICENSE_OK) {
        std::cout << "license OK" << std::endl;
        if (!licenseInfo.linked_to_pc) {
            std::cout << "No hardware signature in license file. This is a 'demo' license that works on every pc." << std::endl
                 << "To generate a 'single pc' license call 'issue license' with option -s " << std::endl
                 << "and the hardware identifier obtained before." << std::endl;
        }
    }
    if (result != LICENSE_OK) {
        size_t pc_id_sz = LCC_API_PC_IDENTIFIER_SIZE + 1;
        char pc_identifier[LCC_API_PC_IDENTIFIER_SIZE + 2];
        std::cout << "license ERROR :" << std::endl;
        std::cout << "    " << stringByEventType[result].c_str() << std::endl;
        if (identify_pc(STRATEGY_DEFAULT, pc_identifier, &pc_id_sz, nullptr)) {
            std::cout << "pc signature is :" << std::endl;
            std::cout << "    " << pc_identifier << std::endl;
        } else {
            cerr << "errors in identify_pc" << std::endl;
        }
    }

    return result;
}

int main()
{
	std::std::cout << "Hello CMake." << std::std::endl;
	return 0;
}