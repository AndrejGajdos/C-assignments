#ifndef CSVPARSER_H_
#define CSVPARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS 0
#define INVALID_ARGUMENTS 1
#define FILE_NOT_FOUND 2
#define OTHER_ERROR 3
#define PARSING_ERROR 4

/**
 * Amount of memory (e.g. number of lines) allocated at once while reading input file.
 */
#define MEM_SIZE 100

/**
 * Structure for storing information used in GPX tag.
 * lat - lattitude (in degrees, north)
 * lon - longitude (in degrees, east)
 * ele - elevation (in meters)
 * time - time in 24 hour format hh:mm:ss (e.g. 06:43:50)
 * date - date in format yyyy-mm-dd (e.g. 2011-09-25)
 */
typedef struct gpxTag {
	double lat;
	double lon;
	double ele;
	char time[9];
	char date[11];
} gpxTag;

/**
 * Parses line from csv file and stores information into tag.
 * @param file pointer into input file
 * @param tag pointer to tag where to store GPX information
 * @return SUCCESS when line was successfully parsed,
 *         PARSING_ERROR when the line is not in requested format
 *         EOF when end of file is reached
 *         INVALID_ARGUMENTS when some parameter is NULL
 *         OTHER_ERROR when some error occures while reading
 */
int parseCSVLine(FILE * file, gpxTag * tag);

/**
 * Writes one gpx tag into output file. Whitespace between xml tags does not
 * matter.
 * @param file pointer into output file
 * @param tag ponter to the tag that should be written
 * @return SUCCESS when line was successfully written,
 *         INVALID_ARGUMENTS when some parameter is NULL
 *         OTHER_ERROR when some error occures while writing
 */
int writeGPXTag(FILE * file, gpxTag * tag);

/**
 * Writes XML/GPX header into file.
 * @param file file where to write header
 * @return SUCCESS on success, INVALID_ARGUMENTS in case of invalid parameter
 */
int writeHeader(FILE * file);

/**
 * Writes XML/GPX footer into file.
 * @param file file where to write footer
 * @return SUCCESS on success, INVALID_ARGUMENTS in case of invalid parameter
 */
int writeFooter(FILE * file);


#endif /* CSVPARSER_H_ */
