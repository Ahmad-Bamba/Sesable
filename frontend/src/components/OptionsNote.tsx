import React, { useEffect, useState } from "react";
import { debounceTime } from "../lib/Constants";

interface OptionsNoteProps {}

function OptionsNote(props: OptionsNoteProps) {
    const [noteTitle, setNoteTitle] = useState<string>("untitled");

    // Debouncing so we don't spam the server with changes to the document title
    useEffect(() => {
        const timer = setTimeout(() => { 
            setNoteTitle(noteTitle);
            console.log("Document title is now:", noteTitle);
        }, debounceTime);
        return () => clearTimeout(timer);
    }, [noteTitle]);

    return (
        <>
            <ul>
                <li>
                    <input 
                        type="text"
                        value={noteTitle}
                        onChange={event => setNoteTitle(event.target.value)}
                    />
                </li>
                <li></li>
            </ul>
        </>
    );
}

export default OptionsNote;