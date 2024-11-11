<script lang="ts">
  export let humidity: number;
  export let temperature: number;
  export let title: string = "";
  export let titleLeft: string = "";
  export let titleRight: string = "";
  import BatteryIcon from "./BatteryIcon.svelte";
  import CircularSlider from "./CircularSlider.svelte";
  import heatIcon from "../assets/heating.svg";
  import HumidityIcon from "./HumidityIcon.svelte";
  import settingsIcon from "../assets/settings.svg";
  import SignalIcon from "./SignalIcon.svelte";
  import TemperatureIcon from "./TemperatureIcon.svelte";
</script>

<div style="width: 100%;aspect-ratio: 1/1">
  <CircularSlider
    bind:value={temperature}
    min={10}
    max={30}
    stroke={10}
    {title}
    {titleLeft}
    {titleRight}
	rangeStart={temperature}
	rangeStop={21}
    --stroke-color="#f2c894"
  >
    <CircularSlider bind:value={humidity} min={0} max={100} stroke={10}
	rangeStart={40}
	rangeStop={60}
	--stroke-color="#9fc0de">
      <div class="slider-content">
        <span style="white-space:nowrap"
          ><TemperatureIcon value={temperature} />{temperature.toLocaleString(undefined, {
            minimumFractionDigits: 1,
            maximumFractionDigits: 1,
          })}</span
        >
        <span style="white-space:nowrap"><HumidityIcon value={humidity} />{humidity}%</span>
      </div>
      <div class="badge top" data-tooltip="Target temperature {temperature}℃">
        <img src={heatIcon} alt="" />{temperature}℃
      </div>
      <div class="badge top left">
        <SignalIcon value={-80} />
      </div>
      <div class="badge top right">
        <SignalIcon value={-90} />
      </div>
      <div class="badge left">
        <BatteryIcon value={50} />
      </div>
      <div class="badge right">
        <BatteryIcon value={50} />
      </div>
      <div class="badge bottom">
        {temperature.toLocaleString(undefined, {
          minimumFractionDigits: 1,
          maximumFractionDigits: 1,
        }) + "℃"}
      </div>
      <div class="badge bottom left"></div>
      <div class="badge bottom right">
        <img src={settingsIcon} alt="" />
      </div>
    </CircularSlider>
  </CircularSlider>
</div>

<!-- 
    tomato
    v#3399FF
   -->
<!-- <CircularSlider {value} angle={(2 * 3.14 * value) / 365} /> -->

<style>
  .slider-content {
    top: 50%;
    left: 50%;
    font-family: "Calibri", sans-serif;
    font-size: calc(var(--slider-radius) / 2.5);
    font-weight: 300;
    transform: translate(-50%, -50%);
    position: absolute;
    line-height: normal;
    text-align: center;
  }

  .badge {
    opacity: 0.3;
    position: absolute;
  }
  .badge.top {
    left: 50%;
    top: 8%;
    transform: translate(-50%, 0);
  }

  .badge.top.left {
    left: 13%;
    top: 13%;
    transform: none;
  }

  .badge.top.right {
    right: 13%;
    top: 13%;
    -webkit-transform: scaleX(-1);
    transform: scaleX(-1);
  }

  .badge.left {
    left: 5%;
    top: 50%;
    transform: translate(0, -50%);
  }

  .badge.right {
    right: 5%;
    top: 50%;
    transform: translate(0, -50%);
  }

  .badge.bottom {
    left: 50%;
    bottom: 8%;
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
</style>
