<script lang="ts">
  import type { DeviceStatus, SensorStatus } from "../interfaces";
  import Indicators from "./Indicators.svelte";

  export let devices: DeviceStatus[];
  export let sensors: SensorStatus[] | undefined;
  export let apiUrl: string;

  async function onReferenceSensorChange(
    event: Event & { currentTarget: EventTarget & HTMLSelectElement }
  ) {
    const sensorId = event.currentTarget.getAttribute("data-sensor");
    const device = devices.find((dev) => dev.id === sensorId);
    const response = await fetch(apiUrl + "thermostat", {
      method: "POST",
      body: JSON.stringify({
        id: device?.id,
        referenceSensor: device?.referenceSensor,
      }),
      headers: {
        "Content-Type": "application/json",
      },
    });

    if (!response.ok) {
      // Handle
    }
  }
</script>

<article class="devices-list">
  {#each devices as device}
    <details id={device.id}>
      <summary class="secondary">
        <div class="row">
          <!-- <span>{name}</span> -->
          <div class="col-sm-4 col-md-4 col-lg-6 col-xl-6">
            <b>{device.name}</b>
          </div>
          <div class="col-sm-8 col-md-8 col-lg-6 col-xl-6">
            <Indicators {device} />
          </div>
        </div>

        {#if sensors}
          <div class="row">
            <div class="col-sm-4 col-md-4 col-lg-6 col-xl-6">
              <select
                bind:value={device.referenceSensor}
                data-sensor={device.id}
                on:change={onReferenceSensorChange}
              >
                <option value="" selected={device.referenceSensor === ""}
                  >{device.model}
                  {device.serial} ({device.temperature}℃)</option
                >
                {#each sensors as sensor}
                  <option
                    selected={sensor.id === device.referenceSensor}
                    value={sensor.id}
                    >{sensor.name} ({sensor.temperature}℃)</option
                  >
                {/each}
                {#if device.referenceSensor && !sensors.find((sensor) => sensor.id == device.referenceSensor)}
                  <option selected={true} value={device.referenceSensor}>
                    {device.referenceSensor} (Unavailable)
                  </option>
                {/if}
              </select>
            </div>
            <div class="col-sm-8 col-md-8 col-lg-6 col-xl-6">
              {#each sensors as sensor}
                {#if sensor.id === device.referenceSensor}
                  <Indicators device={sensor} />
                {/if}
              {/each}
            </div>
          </div>
        {/if}
      </summary>
    </details>
  {/each}
</article>
