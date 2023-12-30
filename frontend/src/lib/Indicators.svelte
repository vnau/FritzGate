<script lang="ts">
  import humidityIcon from "../assets/humidity.svg";
  import temperatureIcon from "../assets/thermometer.svg";
  import heatIcon from "../assets/heating.svg";
  import signalIcon from "../assets/signal.svg";
  import type { DeviceStatus } from "../interfaces";

  export let device: Partial<DeviceStatus>;
</script>

<div class="row">
  <div
    class="col {device.referenceSensor ? 'strikeout' : ''}"
    data-tooltip="Actual temperature {device.temperature}℃"
  >
    <img src={temperatureIcon} alt="" />
    {device.temperature}℃
  </div>
  {#if device.targetTemperature}
    <div
      class="col"
      data-tooltip="Target temperature {device.targetTemperature}℃"
    >
      <img src={heatIcon} alt="" />
      {device.targetTemperature}℃
    </div>
  {:else}
    <div class="col" data-tooltip="Actual humidity {device.humidity}%">
      {#if device.humidity}
        <img src={humidityIcon} alt="" />
        {Math.round(device.humidity)}%
      {/if}
    </div>
  {/if}
  <div class="col" data-tooltip="Signal strength {device.rssi} dB">
    <img src={signalIcon} alt="" />
    {device.rssi} dB
  </div>
  <div class="col" data-tooltip="Battery status  {device.battery}%">
    {device.battery}%
  </div>
</div>
