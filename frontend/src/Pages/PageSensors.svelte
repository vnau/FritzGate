<script lang="ts">
  import type { DeviceStatus } from "../interfaces";
  import DevicesList from "../lib/DevicesList.svelte";
  import WaitBox from "../lib/WaitBox.svelte";
  import Indicator from "../lib/Indicator.svelte";

  export let apiUrl: string;
  export let data: any;

  let sensors: DeviceStatus[] | null = null;
  var timestamp = 0;
  $: {
    if (data) {
      ({ sensors } = data);
      timestamp =
        sensors && sensors.length > 0
          ? Math.max(...sensors.sort((a, b) => a.id.localeCompare(b.id)).map((v) => v.seriesTimestamp))
          : 0;
    }
  }
</script>

{#if !sensors}
  <WaitBox message="trying to connect to the gateway" details="this buddy gossips too much with the sensors" />
{:else if sensors.length === 0}
  <WaitBox
    message="trying hard to find sensors nearby"
    details="Fritzgate uses the Theengs Decoder, which supports over 70 models of temperature sensors."
  />
{:else}
  <!-- <DevicesList devices={sensors} sensors={undefined} {apiUrl} /> -->
{/if}
<!-- <input type="range" bind:value={temperature} min={10} max={30} step={0.1} />
<input type="range" bind:value={humidity} min={0} max={100} step={0.1} /> -->
<article class="devices-list">
<span style="" class="row">
  {#each sensors ?? [] as sensor}
  <div class="col-6 col-sm-6 col-md-4 col-lg-3 p-0">
    <Indicator
      temperature={sensor.temperature}
      humidity={Math.round(sensor.humidity)}
      title={"Living room"}
      titleLeft={sensor.data}
      titleRight={sensor.name}
    />
  </div>
  {/each}
  <!-- <Indicator {temperature} {humidity} title={"Kitchen"} /> -->
</span>
</article>