interface SliderProps {
    boxText?: string;
    handleChange?: () => void;
}

function SliderText(s: SliderProps) {
    if (s.boxText === undefined) {
        return null;
    }
    if (s.boxText === "") {
        return null;
    }
    return (<span>{s.boxText}</span>);
}

function SliderInput (hc: SliderProps) {
    if (hc.handleChange === undefined) {
        return (<input type="checkbox"></input>);
    }
    return (<input type="checkbox" onChange={hc.handleChange}></input>);
}

function Slider(props: SliderProps) {
    return (
        <label className="switch">
            <SliderInput handleChange={props.handleChange} />
            <SliderText boxText={props.boxText} />
        </label>
    );
}

export default Slider;