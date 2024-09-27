<script lang="ts">
  import type { DeviceStatus } from "../interfaces";
  import DevicesList from "../lib/DevicesList.svelte";
  import WaitBox from "../lib/WaitBox.svelte";
  import { router } from "tinro";

  export let apiUrl: string;
  export let data: any;

  let thermostats: DeviceStatus[] = [];
  let sensors: DeviceStatus[] = [];
  var timestamp = 0;

  $: {
    if (data) {
      if (
        data?.fritz?.status == "FAILURE" ||
        data?.fritz?.status == "NOT_CONFIGURED" ||
        data?.fritz?.status == "CONFIGURED" ||
        data?.fritz?.status == "CONNECTING"
      ) {
        router.goto("/setup");
      }
      ({ thermostats, sensors } = data);
      timestamp = thermostats && thermostats.length > 0 ? Math.max(...thermostats.map((v) => v.seriesTimestamp)) : 0;
    }
  }
</script>

{#if !thermostats || thermostats.length === 0}
  <WaitBox message="waiting for data from FRITZ!Box" details="can't find any thermostat yet" />
{:else}
  <DevicesList devices={thermostats} {sensors} {apiUrl} />
{/if}
