CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wno-long-long
LDFLAGS=-std=c++17 -Wall -pedantic -Wno-long-long
SRC=$(wildcard src/*.cpp src/*/*.cpp)

all: volckric

# create all binaries
volckric: main.o CApplication.o CCalendar.o CCalendarFinder.o CCalendarImporter.o CConflictSolver.o CDatetime.o CDisplayCalendar.o CDisplayDaily.o CDisplayMonthly.o CDisplayWeekly.o CEvent.o CEventExporter.o CEventRecurring.o CEventSimple.o CHelpers.o CTime.o
	$(LD) $(LXXFLAGS) -o $@ $^

clean:
	rm -f volckric *.o

# match binaries to the cpp files that are directly in src
%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# match binaries to the cpp files that are in subfolders
%.o: src/*/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: volckric
	./volckric

compile: volckric

main.o: src/main.cpp src/CApplication.h
CApplication.o: src/CApplication.cpp src/CApplication.h
CCalendar.o: src/CCalendar.cpp src/CCalendar.h
CCalendarFinder.o: src/CCalendarFinder.cpp src/CCalendarFinder.h
CCalendarImporter.o: src/importExport/CCalendarImporter.cpp src/importExport/CCalendarImporter.h
CConflictSolver.o: src/CConflictSolver.cpp src/CConflictSolver.h
CDatetime.o: src/utils/CDatetime.cpp src/utils/CDatetime.h
CDisplayCalendar.o: src/display/CDisplayCalendar.cpp src/display/CDisplayCalendar.h
CDisplayDaily.o: src/display/CDisplayDaily.cpp src/display/CDisplayDaily.h
CDisplayMonthly.o: src/display/CDisplayMonthly.cpp src/display/CDisplayMonthly.h
CDisplayWeekly.o: src/display/CDisplayWeekly.cpp src/display/CDisplayWeekly.h
CEvent.o: src/event/CEvent.cpp src/event/CEvent.h
CEventExporter.o: src/importExport/CEventExporter.cpp src/importExport/CEventExporter.h
CEventRecurring.o: src/event/CEventRecurring.cpp src/event/CEventRecurring.h
CEventSimple.o: src/event/CEventSimple.cpp src/event/CEventSimple.h
CHelpers.o: src/utils/CHelpers.cpp src/utils/CHelpers.h
CTime.o: src/utils/CTime.cpp src/utils/CDatetime.h
