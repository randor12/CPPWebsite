#include "Crow/include/crow.h"
#include <string>

// Helper function to create a response with CORS headers
crow::response create_cors_response(const std::string& body) {
    crow::response res;
    res.body = body;
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
    res.set_header("Content-Type", "application/json");
    return res;
}

int main() {
    crow::SimpleApp app;

    // Define a route for data
    CROW_ROUTE(app, "/api/data")
    ([]() {
        std::string json = R"({
            "items": [
                {"id": 0, "name": "Item 0", "value": 0},
                {"id": 1, "name": "Item 1", "value": 10},
                {"id": 2, "name": "Item 2", "value": 20},
                {"id": 3, "name": "Item 3", "value": 30},
                {"id": 4, "name": "Item 4", "value": 40}
            ],
            "count": 5
        })";
        
        return create_cors_response(json);
    });

    // OPTIONS route for CORS preflight requests
    CROW_ROUTE(app, "/api/data").methods("OPTIONS"_method)
    ([]() {
        crow::response res;
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.code = 204; // No content
        return res;
    });

    // Run the server
    app.port(3001).multithreaded().run();
    
    return 0;
}
