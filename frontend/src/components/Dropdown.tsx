import React, { ChangeEvent } from "react";

interface OptionLike {
    value: string;
    displayName: string;
}

interface Props {
    name: string;
    displayName?: string;
    options: OptionLike[];
    registerChoiceCB?: (choice: string) => void;
}

function Dropdown(props: Props) { 
    const callback = function(e: ChangeEvent<HTMLSelectElement>) {
    if (props.registerChoiceCB) {
        props.registerChoiceCB(e.target.value);
    }
    };

    return (
        <>
            <label className="DropdownLabel">{props.displayName === undefined ? props.name : props.displayName}</label>
            <select name={props.name} className="DropdownSelect" onChange={callback}>
                {props.options.map((object, i) => {
                    return (
                        <option key={i} value={object.value}>{object.displayName}</option>
                    );
                })}
            </select>
        </>
    );
}

export default Dropdown;
