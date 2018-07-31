#ifndef __LIB_MIDI_PARSER_HEADER_
#define __LIB_MIDI_PARSER_HEADER_

#include <stdbool.h>

typedef enum {
	MidiSequenceNumber,
	MidiTextEvent,
	MidiNewLyric,
	MidiNewMarker,
	MidiNewCuePoint,
	MidiNewChannelPrefix,
	MidiPortChange,
	MidiTempoChanged,
	MidiSMTPEOffset,
	MidiNewTimeSignature,
	MidiNewKeySignature,
	MidiSequencerSpecificEvent,
	MidiNoteReleased,
	MidiNotePressed,
	MidiPolyphonicPressure,
	MidiControllerValueChanged,
	MidiProgramChanged,
	MidiPressureOfChannelChanged,
	MidiPitchBendChanged,
} EventType;

typedef	struct {
	EventType	type;
	int		timeToAppear;
	void		*infos;
} Event;

typedef	struct EventList_s EventList;
struct EventList_s {
	Event		*data;
	EventList	*prev;
	EventList	*next;
};

typedef struct {
	char		*copyright;
	char		*name;
	char		*instrumentName;
	EventList	events;
} Track;

typedef struct {
	unsigned short	format;
	short		nbOfTracks;
	char		fps;
	short		ticks;
	int		numberOfNotes;
	Track		*tracks;
} MidiParser;

bool		parseMidiTrack(unsigned char *buffer, int buffLen, Track *track, bool outputDebug, MidiParser *result);
MidiParser	*parseMidi(char *path, bool outputDebug);
char		*getNoteString(char note);
void		deleteEventList(EventList *list);
void		deleteTrack(Track *track);
void		deleteMidiParserStruct(MidiParser *result);

#endif