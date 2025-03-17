<script lang="ts">
  export let humidity: number;
  export let temperature: number;
  export let title: string = "";
  export let titleLeft: string = "";
  export let signalLeft: number | undefined = undefined;
  export let chargeLeft: number | undefined = undefined;
  export let temperatureLeft: number | undefined = undefined;
  export let targetTemperature: number | undefined = undefined;

  export let titleRight: string = "";
  export let signalRight: number | undefined = undefined;
  export let chargeRight: number | undefined = undefined;

  import Gauge from "svelte-gauge";
  import heatIcon from "../assets/heating.svg";
  import settingsIcon from "../assets/settings.svg";
  import BatteryIcon from "./BatteryIcon.svelte";
  import HumidityIcon from "./HumidityIcon.svelte";
  import SignalIcon from "./SignalIcon.svelte";
  import TemperatureIcon from "./TemperatureIcon.svelte";
</script>

<div style="width: 100%;aspect-ratio: 1/1">
  <Gauge
    class="indicator-gauge"
    bind:value={temperature}
    start={10}
    stop={30}
    stroke={10}
    labelsCentered={true}
    labels={[titleLeft, title, titleRight]}
    segments={[[temperature, targetTemperature ?? temperature]]}
    --stroke-color="#f2c894"
  >
    <Gauge
      bind:value={humidity}
      stroke={10}
      segments={[[40, 60]]}
      --stroke-color="#9fc0de"
    >
      <div class="slider-content">
        <span style="white-space:nowrap"
          ><TemperatureIcon value={temperature} />{temperature.toLocaleString(
            undefined,
            {
              minimumFractionDigits: 1,
              maximumFractionDigits: 1,
            }
          )}</span
        >
        <span style="white-space:nowrap"
          ><HumidityIcon value={humidity} />{humidity}%</span
        >
      </div>
      {#if targetTemperature}
        <div
          class="badge top"
          data-tooltip="Target temperature {targetTemperature}℃"
        >
          <img src={heatIcon} alt="" />{targetTemperature}℃
        </div>
      {/if}
      <div class="badge top left">
        <SignalIcon value={signalLeft} />
      </div>
      <div class="badge top right">
        <SignalIcon value={signalRight} />
      </div>
      <div class="badge left">
        <BatteryIcon value={chargeLeft} />
      </div>
      <div class="badge right">
        <BatteryIcon value={chargeRight} />
      </div>
      {#if temperatureLeft}
        <div class="badge bottom">
          {temperatureLeft?.toLocaleString(undefined, {
            minimumFractionDigits: 1,
            maximumFractionDigits: 1,
          }) + "℃"}
        </div>
      {/if}
      <div class="badge bottom left"></div>
      {#if false}
        <div class="badge bottom right">
          <img src={settingsIcon} alt="" />
        </div>
      {/if}
    </Gauge>
  </Gauge>
</div>

<style lang="scss">
  .slider-content {
    top: 50%;
    width: 100%;
    left: 50%;
    font-size: calc(var(--gauge-radius) / 2.5);
    font-weight: 300;
    transform: translate(-50%, -50%);
    position: absolute;
    display: grid;
  }

  .badge {
    opacity: 0.3;
    position: absolute;
  }
  .badge.top {
    left: 50%;
    top: 2%;
    transform: translate(-50%, 0);
    text-wrap: nowrap;
  }

  .badge.top.left {
    left: 8%;
    top: 13%;
    transform: none;
  }

  .badge.top.right {
    right: 0%;
    top: 13%;
    -webkit-transform: translate(20%, 0%) scaleX(-1);
    transform: translate(20%, 0%) scaleX(-1);
  }

  .badge.left {
    left: 0%;
    top: 50%;
    transform: translate(0, -50%);
  }

  .badge.right {
    right: 0%;
    top: 50%;
    transform: translate(0, -50%);
  }

  .badge.bottom {
    left: 50%;
    bottom: 2%;
    transform: translate(-50%, 0);
  }

  .badge.bottom.left {
    left: 13%;
    bottom: 13%;
    transform: none;
  }

  .badge.bottom.right {
    left: auto;
    top: auto;
    right: 15%;
    bottom: 15%;
  }

  :global(.indicator-gauge) {
    :global(.titles-container) {
      color: lightslategray;
      font-size: 0.7em;
      :global(:first-child) {
        font-size: 1.5em;
      }
    }
  }
</style>
