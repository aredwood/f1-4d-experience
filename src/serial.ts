import SerialPort from "serialport"
// no types, ignore
//@ts-ignore
import Readline from "@serialport/parser-readline"

const SERIAL_PORT = "\\\\.\\COM3"

const port = new SerialPort(SERIAL_PORT, { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));

port.on("open", () => {
    console.log('serial port open');
});

parser.on('data', (data: any) => {
    console.log('ARDUINO:', Buffer.from(data).toString());
});

const setSpeed = (speed:number) => {
    port.write(`${speed}\n`);
    console.log(`HOST: speed: ${speed}`)
}

process.on("exit", port.close)

export {
    setSpeed
}