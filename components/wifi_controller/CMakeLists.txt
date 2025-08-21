idf_component_register(
    SRCS 
        "wifi_controller.c"
        "ap_scanner.c"    
        "sniffer.c"     
    INCLUDE_DIRS "."  
    REQUIRES esp_event esp_wifi
)

