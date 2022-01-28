import { F1TelemetryClient } from "f1-2021-udp";
import { setSpeed } from "./serial";


// get ip address from environment, default to localhost
const IP_ADDRESS = process.env.IP_ADDRESS || "127.0.0.1";

const client: F1TelemetryClient = new F1TelemetryClient({
    address:IP_ADDRESS
});


client.on("carTelemetry",(event) => {
    // TODO, this only works in qualifying
    // because the player's car may not always be the first in the array.
    const [main_car] = event["m_carTelemetryData"]

    const speed = main_car.m_speed;

    setSpeed(speed)
})

client.start()