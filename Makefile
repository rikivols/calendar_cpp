CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wno-long-long

all: compile
	doxygen

deps:
	echo "\n# Autogenerated dependencies:\n" >> Makefile ; $(CC) -MM src/*.cpp src/*/*.cpp examples/tests/*.cpp >> Makefile

# create volckric binary
volckric: main.o CApplication.o CCalendar.o CCalendarFinder.o CCalendarImporter.o CConflictSolver.o CDatetime.o CDisplayCalendar.o CDisplayDaily.o CDisplayMonthly.o CDisplayWeekly.o CEvent.o CEventExporter.o CEventRecurring.o CEventSimple.o CHelpers.o CTime.o
	$(LD) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf volckric *.o *~ testsCalendar Makefile.d doc

.PHONY: doc
doc:
	doxygen

# match binaries to the cpp files that are directly in src
%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# match binaries to the cpp files that are in subfolders
%.o: src/*/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# match test binaries
%.o: examples/tests/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: volckric
	./volckric

testsCalendar: testMain.o testDates.o testConflict.o testCalendarOperations.o CApplication.o CCalendar.o CCalendarFinder.o CCalendarImporter.o CConflictSolver.o CDatetime.o CDisplayCalendar.o CDisplayDaily.o CDisplayMonthly.o CDisplayWeekly.o CEvent.o CEventExporter.o CEventRecurring.o CEventSimple.o CHelpers.o CTime.o
	$(CXX) $(CXXFLAGS) -o $@ $^

run_test:
	./testsCalendar

compile: volckric

compileTests: testsCalendar

# Autogenerated dependencies:

CApplication.o: src/CApplication.cpp src/CApplication.h src/CCalendar.h \
  src/event/CEvent.h src/event/../utils/CDatetime.h \
  src/event/../utils/CHelpers.h src/display/CDisplayDaily.h \
  src/display/CDisplayCalendar.h src/display/../CCalendar.h \
  src/display/../utils/CHelpers.h src/display/CDisplayWeekly.h \
  src/display/CDisplayMonthly.h src/event/CEventSimple.h \
  src/event/CEventRecurring.h src/CConflictSolver.h \
  src/importExport/CEventExporter.h src/importExport/../event/CEvent.h \
  src/importExport/../utils/CHelpers.h \
  src/importExport/CCalendarImporter.h src/importExport/../CCalendar.h \
  src/importExport/../event/CEventRecurring.h \
  src/importExport/../event/CEventSimple.h src/CCalendarFinder.h \
  src/utils/CDatetime.h
CCalendar.o: src/CCalendar.cpp src/CCalendar.h src/event/CEvent.h \
  src/event/../utils/CDatetime.h src/event/../utils/CHelpers.h \
  src/CConflictSolver.h
CCalendarFinder.o: src/CCalendarFinder.cpp src/CCalendarFinder.h \
  src/utils/CDatetime.h src/utils/CHelpers.h src/CCalendar.h \
  src/event/CEvent.h src/event/../utils/CDatetime.h \
  src/importExport/CEventExporter.h src/importExport/../event/CEvent.h \
  src/importExport/../utils/CHelpers.h
CConflictSolver.o: src/CConflictSolver.cpp src/CConflictSolver.h \
  src/CCalendar.h src/event/CEvent.h src/event/../utils/CDatetime.h \
  src/event/../utils/CHelpers.h
main.o: src/main.cpp src/CApplication.h src/CCalendar.h \
  src/event/CEvent.h src/event/../utils/CDatetime.h \
  src/event/../utils/CHelpers.h src/display/CDisplayDaily.h \
  src/display/CDisplayCalendar.h src/display/../CCalendar.h \
  src/display/../utils/CHelpers.h src/display/CDisplayWeekly.h \
  src/display/CDisplayMonthly.h src/event/CEventSimple.h \
  src/event/CEventRecurring.h src/CConflictSolver.h \
  src/importExport/CEventExporter.h src/importExport/../event/CEvent.h \
  src/importExport/../utils/CHelpers.h \
  src/importExport/CCalendarImporter.h src/importExport/../CCalendar.h \
  src/importExport/../event/CEventRecurring.h \
  src/importExport/../event/CEventSimple.h src/CCalendarFinder.h \
  src/utils/CDatetime.h
CDisplayCalendar.o: src/display/CDisplayCalendar.cpp \
  src/display/CDisplayCalendar.h src/display/../CCalendar.h \
  src/display/../event/CEvent.h \
  src/display/../event/../utils/CDatetime.h \
  src/display/../event/../utils/CHelpers.h \
  src/display/../utils/CHelpers.h
CDisplayDaily.o: src/display/CDisplayDaily.cpp \
  src/display/CDisplayDaily.h src/display/CDisplayCalendar.h \
  src/display/../CCalendar.h src/display/../event/CEvent.h \
  src/display/../event/../utils/CDatetime.h \
  src/display/../event/../utils/CHelpers.h \
  src/display/../utils/CHelpers.h
CDisplayMonthly.o: src/display/CDisplayMonthly.cpp \
  src/display/CDisplayMonthly.h src/display/CDisplayCalendar.h \
  src/display/../CCalendar.h src/display/../event/CEvent.h \
  src/display/../event/../utils/CDatetime.h \
  src/display/../event/../utils/CHelpers.h \
  src/display/../utils/CHelpers.h
CDisplayWeekly.o: src/display/CDisplayWeekly.cpp \
  src/display/CDisplayWeekly.h src/display/CDisplayCalendar.h \
  src/display/../CCalendar.h src/display/../event/CEvent.h \
  src/display/../event/../utils/CDatetime.h \
  src/display/../event/../utils/CHelpers.h \
  src/display/../utils/CHelpers.h
CEvent.o: src/event/CEvent.cpp src/event/CEvent.h \
  src/event/../utils/CDatetime.h src/event/../utils/CHelpers.h
CEventRecurring.o: src/event/CEventRecurring.cpp \
  src/event/CEventRecurring.h src/event/CEvent.h \
  src/event/../utils/CDatetime.h src/event/../utils/CHelpers.h
CEventSimple.o: src/event/CEventSimple.cpp src/event/CEventSimple.h \
  src/event/CEvent.h src/event/../utils/CDatetime.h \
  src/event/../utils/CHelpers.h
CCalendarImporter.o: src/importExport/CCalendarImporter.cpp \
  src/importExport/CCalendarImporter.h src/importExport/../CCalendar.h \
  src/importExport/../event/CEvent.h \
  src/importExport/../event/../utils/CDatetime.h \
  src/importExport/../event/../utils/CHelpers.h \
  src/importExport/../event/CEventRecurring.h \
  src/importExport/../event/CEventSimple.h
CEventExporter.o: src/importExport/CEventExporter.cpp \
  src/importExport/CEventExporter.h src/importExport/../event/CEvent.h \
  src/importExport/../event/../utils/CDatetime.h \
  src/importExport/../event/../utils/CHelpers.h \
  src/importExport/../utils/CHelpers.h
CDatetime.o: src/utils/CDatetime.cpp src/utils/CDatetime.h \
  src/utils/CHelpers.h
CHelpers.o: src/utils/CHelpers.cpp src/utils/CHelpers.h
CTime.o: src/utils/CTime.cpp src/utils/CDatetime.h src/utils/CHelpers.h
testCalendarOperations.o: examples/tests/testCalendarOperations.cpp \
  examples/tests/testCalendarOperations.h \
  examples/tests/../../src/CCalendar.h \
  examples/tests/../../src/event/CEvent.h \
  examples/tests/../../src/event/../utils/CDatetime.h \
  examples/tests/../../src/event/../utils/CHelpers.h \
  examples/tests/../../src/event/CEventSimple.h \
  examples/tests/../../src/event/CEventRecurring.h
testConflict.o: examples/tests/testConflict.cpp \
  examples/tests/testConflict.h \
  examples/tests/../../src/CConflictSolver.h \
  examples/tests/../../src/CCalendar.h \
  examples/tests/../../src/event/CEvent.h \
  examples/tests/../../src/event/../utils/CDatetime.h \
  examples/tests/../../src/event/../utils/CHelpers.h \
  examples/tests/../../src/event/CEventRecurring.h \
  examples/tests/../../src/event/CEventSimple.h
testDates.o: examples/tests/testDates.cpp examples/tests/testDates.h \
  examples/tests/../../src/utils/CDatetime.h \
  examples/tests/../../src/utils/CHelpers.h
testMain.o: examples/tests/testMain.cpp examples/tests/testDates.h \
  examples/tests/../../src/utils/CDatetime.h \
  examples/tests/../../src/utils/CHelpers.h \
  examples/tests/testConflict.h \
  examples/tests/../../src/CConflictSolver.h \
  examples/tests/../../src/CCalendar.h \
  examples/tests/../../src/event/CEvent.h \
  examples/tests/../../src/event/../utils/CDatetime.h \
  examples/tests/../../src/event/CEventRecurring.h \
  examples/tests/../../src/event/CEventSimple.h \
  examples/tests/testCalendarOperations.h
