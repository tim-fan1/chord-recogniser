#pragma once

#include <set>
#include <map>
#include <string>
#include <utility>

class ChordAnalyser
{
public:
    ChordAnalyser(std::set<int> _notes)
    :
    notes { _notes },
    uniqueNotes { _uniqueNotes() }
    {
        analyseChords();
    }
    /** find allChordNames. */
    void analyseChords()
    {
        int n = (int)uniqueNotes.size();
        if (n < 3) return;
        /** find allChordNames */
        // first analyse with no slash note.
        std::string slash = "";
        analyseChord("");
        // now analyse with slash note.
        auto head = notes.begin();
        if (head != notes.end())
            slash = midi_to_string[(*head)%12];
        else
            return;
        for (int i = 0; i < n-1; i++)
            analyseChord(slash);
        return;
    }
    /** analyse uniqueNotes (add to allChordNames). after finished, move the lowest note up an octave.
     *  inv: uniqueNotes has at least 3 notes. */
    void analyseChord(std::string slash)
    {
        // intervals[i] is true if the chord has an interval of i semitones from the root.
        bool intervals[12] = { false };
        std::set<int>::iterator head = uniqueNotes.begin();
        int root = *head;
        for (auto it = uniqueNotes.begin(); it != uniqueNotes.end(); it++)
            intervals[(*it)-root] = true;
        /** generate chord name */
        // work out root.
        std::string res = midi_to_string[root%12];
        int complexity = 0;
        // work out tonality (maj/min/dim/aug).
        if (intervals[7])
        {
            if (intervals[4])
            {
                complexity += 1;
                res += "maj";
                intervals[4] = false;
            }
            else if (intervals[3])
            {
                complexity += 1;
                res += "min";
                intervals[3] = false;
            }
            else if (intervals[2])
            {
                complexity += 5;
                res += "sus2";
                intervals[2] = false;
            }
            else if (intervals[5])
            {
                complexity += 3;
                res += "sus4";
                intervals[5] = false;
            }
            else // power chord.
            {
                complexity += 6;
                res += "5";
            }
            intervals[7] = false;
        }
        else if (intervals[3] && intervals[6])
        {
            complexity += 2;
            res += "dim";
            intervals[3] = intervals[6] = false;
        }
        else if (intervals[4] && intervals[8])
        {
            complexity += 2;
            res += "aug";
            intervals[4] = intervals[8] = false;
        }
        else
        {
            nextPermutation();
            return;
        }
        // work out sevenths (maj/min)
        if (intervals[11])
        {
            complexity += 2;
            res += "(maj7)";
            intervals[11] = false;
        }
        else if (intervals[10])
        {
            complexity += 2;
            res += "(min7)";
            intervals[10] = false;
        }
        // work out other extensions (9/11/13).
        if (intervals[1])
        {
            complexity += 3;
            res += "(b9)";
            intervals[1] = false;
        }
        if (intervals[2])
        {
            complexity += 3;
            res += "(9)";
            intervals[2] = false;
        }
        if (intervals[3])
        {
            complexity += 3;
            res += "(#9)";
            intervals[3] = false;
        }
        if (intervals[5])
        {
            complexity += 3;
            res += "(11)";
            intervals[4] = false;
        }
        if (intervals[6])
        {
            complexity += 3;
            res += "(#11)";
            intervals[6] = false;
        }
        if (intervals[8])
        {
            complexity += 3;
            res += "(b13)";
            intervals[8] = false;
        }
        if (intervals[9])
        {
            complexity += 3;
            res += "(13)";
            intervals[9] = false;
        }
        if (intervals[10])
        {
            complexity += 3;
            res += "(#13)";
            intervals[10] = false;
        }
        /** account for slash */
        if (slash.compare("") != 0)
        {
            res += "/";
            res += slash;
        }
        /** add chord to allChordNames. */
        allChordNames.insert(std::make_pair(complexity,res));
        nextPermutation();
        return;
    }
    /** prepare uniqueNotes for the next permuation. i.e. move lowest note up an octave.*/
    void nextPermutation()
    {
        auto it = uniqueNotes.begin();
        int temp = *it;
        uniqueNotes.erase(it);
        uniqueNotes.insert(temp+12);
        return;
    }
    /** string representation of notes. used for debugging purposes. */
    std::string getMidiNotesString()
    {
        std::string res("");
        for (int note : notes)
        {
            res += std::to_string(note);
            res += " ";
        }
        return res;
    }
    /** the unique notes in notes. res.begin() is the lowest note in the original notes. */
    std::set<int> _uniqueNotes()
    {
        std::set<int> res;
        std::set<int>::iterator it = notes.begin();
        if (it == notes.end()) return res;
        int lowest = *it;
        for (int note : notes) {
            int dist = (note - lowest) % 12;
            res.insert(lowest + dist);
        }
        return res;
    }
    /** the most likely "CMaj7"-like representation of chord. */
    std::string getCommonName()
    {
        std::string commonName;
        if (!allChordNames.size())
            return "No Chord";
        auto it = allChordNames.begin();
        if (it == allChordNames.end())
            return "No Chord";
        return it->second;
    }
    /** all "CMaj7"-like representations of the chord ordered by complexity (head is most likely). */
    std::set<std::pair<int,std::string>> getAllChordNames() { return allChordNames; }
private:
    std::set<int> notes;
    std::set<int> uniqueNotes;
    std::set<std::pair<int,std::string>> allChordNames;
    std::string midi_to_string[12] = {"C","C#","D","Eb","E","F","F#","G","Ab","A","Bb","B"};
};
