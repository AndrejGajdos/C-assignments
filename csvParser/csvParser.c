/*
 ============================================================================
 Name        : csvParser.c
 Author      : 359234
 Copyright   : 359234@mail.muni.cz
 Description : GPS parsing
 ============================================================================
 */

#include "csvParser.h"


int parseCSVLine(FILE * file, gpxTag * tag) {
	
	char line[101];
	memset(line,0,101);
	if ((file==NULL)||(tag==NULL))
        return INVALID_ARGUMENTS;


    fgets (line, 100, file);
    if (line[0] == '\0')
		return EOF;


    int countCommas = 0;
    for(unsigned int i=0; i<strlen(line); i++)
    {
        if (line[i] == ',')
        {
            countCommas++;
        }
    }

    if (countCommas != 10)
        return OTHER_ERROR;

    //	Split one row into arrays
    char rok[5];
    memset(rok,0,5);
    char mesiac[3];
    memset(mesiac,0,3);
    char den[3];
    memset(den,0,3);
    char hodina[3];
    memset(hodina,0,3);
    char minuta[3];
    memset(minuta,0,3);
    char sekunda[3];
    memset(sekunda,0,3);
    char sirka[10];
    memset(sirka,0,10);
    char dlzka[10];
    memset(dlzka,0,10);
    char vyska[8];
    memset(vyska,0,8);
    char* substring;
    int year,month,day,hour,minute,second;
    double lat,lon,ele;
    char date[11];
    memset(date,0,11);
    char time[9];
    memset(time,0,9);

    substring = strstr(line,",")+3;
    strncpy(rok,substring,4);
    year = atoi(rok);

    substring = strstr(line,"/")+1;
    strncpy(mesiac,substring,2);
    month = atoi(mesiac);

    substring = strstr(line,"/")+4;
    strncpy(den,substring,2);
    day = atoi(den);

    strcat(date,rok);
    strcat(date,"-");
    strcat(date,mesiac);
    strcat(date,"-");
    strcat(date,den);

    substring = strstr(line,":")-2;
    strncpy(hodina,substring,2);
    hour = atoi(hodina);

    substring = strstr(line,":")+1;
    strncpy(minuta,substring,2);
    minute = atoi(minuta);

    substring = strstr(line,":")+4;
    strncpy(sekunda,substring,2);
    second = atoi(sekunda);

    strcat(time,hodina);
    strcat(time,":");
    strcat(time,minuta);
    strcat(time,":");
    strcat(time,sekunda);

    substring = strstr(line,":")+7;
    strncpy(sirka,substring,9);
    lat = strtod(sirka, NULL);


    substring = strstr(line,"N")+2;
    strncpy(dlzka,substring,9);
    lon = strtod(dlzka, NULL);

    substring = strstr(line,"E")+2;
    strncpy(vyska,substring,7);
    ele = strtod(vyska, NULL);

    if(lat == 0.0 || lon == 0.0 || ele == 0.0)
    		return PARSING_ERROR;

    // If items are correct
    if ((year > 1970) && (year <= 9999) && (day>=1) && (day<=31) && (month>=1) && (month<=12) && (hour>=0) && (hour<=23) && (minute>=0) && (minute<=59) && (second>=0) && (second<=59))
    {
        tag->lat = lat;
        tag->lon = lon;
        tag->ele = ele;
        for (int i=0;i<=8;i++)
        {
            tag->time[i] = time[i];
        }
        //tag->(time[9]) = NULL;
        for (int i=0;i<=10;i++)
        {
            tag->date[i] = date[i];
        }
        //tag->date[11] = NULL;

        return SUCCESS;
    }

    else
        return OTHER_ERROR;

}

int writeGPXTag(FILE * file, gpxTag * tag)
{
	if ((file==NULL)||(tag==NULL))
	{
	    return INVALID_ARGUMENTS;
	}

    fprintf(file,"<trkpt lat=\"%f\" lon=\"%f\">\n<ele>%.3f</ele>\n<time>%sT%sZ</time>\n<sym>Dot</sym>\n</trkpt>",tag->lat,tag->lon,tag->ele,tag->date,tag->time);

	return SUCCESS;
}

int writeHeader(FILE * file) {
	if (file == NULL) {
		return INVALID_ARGUMENTS;
	}
	fprintf(
			file,
			"<?xml version=\"1.0\" standalone=\"yes\"?>\n"
				"<gpx version=\"1.0\" creator=\"PB071\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
				"xmlns=\"http://www.topografix.com/GPX/1/0\""
				" xsi:schemaLocation=\"http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd\">\n"
				"<trk><name>Holux GPS Track</name><trkseg>\n");
	return SUCCESS;
}

int writeFooter(FILE * file) {
	if (file == NULL) {
		return INVALID_ARGUMENTS;
	}
	fprintf(file, "</trkseg></trk></gpx>\n");
	return SUCCESS;
}
