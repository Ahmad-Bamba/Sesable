import React from 'react';
import OptionsFile from "./OptionsFile";
import OptionsText from "./OptionsNote";

interface OptionsProps {}

function Options(props : OptionsProps) {
    return (
        <>
            <OptionsFile />
            <OptionsText />
        </>
    );
}

export default Options;