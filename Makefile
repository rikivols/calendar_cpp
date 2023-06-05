CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wno-long-long
LDFLAGS=-std=c++17 -Wall -pedantic -Wno-long-long

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
