#ifndef   HKPD_COFIG
#define   HKPD_COFIG


//config port for row
#define  HKPD_ROWS_PORT MDIO_PORTB
#define  HKPD_R1_PIN    MDIO_PIN_0
#define  HKPD_R2_PIN    MDIO_PIN_1
#define  HKPD_R3_PIN    MDIO_PIN_2
#define  HKPD_R4_PIN    MDIO_PIN_3





#define  HKPD_COLS_PORT   MDIO_PORTB
#define  HKPD_C1_PIN      MDIO_PIN_4
#define  HKPD_C2_PIN      MDIO_PIN_5
#define  HKPD_C3_PIN      MDIO_PIN_6
#define  HKPD_C4_PIN      MDIO_PIN_7

//configuration for pattern of KPD
#define HKPD_KPD        {'0','1','2','3',\
                         '4','5','6','7',\
	                     '8','9','*',':',\
	                     '-','+','/','='\
	}



#endif
