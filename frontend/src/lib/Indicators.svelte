<script lang="ts">
  import humidityIcon from "../assets/humidity.svg";
  import temperatureIcon from "../assets/thermometer.svg";
  import heatIcon from "../assets/heating.svg";
  import type { DeviceStatus } from "../interfaces";
  import BatteryIcon from "./BatteryIcon.svelte";
  import SignalIcon from "./SignalIcon.svelte";
  import HumidityIcon from "./HumidityIcon.svelte";
  import TemperatureIcon from "./TemperatureIcon.svelte";

  export let device: Partial<DeviceStatus>;
</script>

<div class="row">
  <div class="col {device.referenceSensor ? 'strikeout' : ''}" data-tooltip="Actual temperature {device.temperature}℃">
    <TemperatureIcon value={device.temperature}/>
    {device.temperature?.toLocaleString(undefined, {
      minimumFractionDigits: 1,
      maximumFractionDigits: 1,
    })}℃
  </div>
  {#if device.targetTemperature}
    <div class="col" data-tooltip="Target temperature {device.targetTemperature}℃">
      <img src={heatIcon} alt="" />
      {device.targetTemperature}℃
    </div>
  {:else}
    <div class="col" data-tooltip="Actual humidity {device.humidity}%">
      {#if device.humidity}
        <HumidityIcon value={device.humidity} />
        {Math.round(device.humidity)}%
      {/if}
    </div>
  {/if}
  <div class="col" data-tooltip="Signal strength {device.rssi} dB">
    <SignalIcon value={device.rssi} />
  </div>
  <div class="col" data-tooltip="Battery status  {device.battery}%">
    <BatteryIcon value={device.battery} />
  </div>
</div>
