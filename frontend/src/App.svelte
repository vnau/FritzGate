<script lang="ts">
  import "./app.scss";
  import { Route, active } from "tinro";

  import PageRouterLogin from "./Pages/PageRouterLogin.svelte";
  import PageSensors from "./Pages/PageSensors.svelte";
  import PageThermostats from "./Pages/PageThermostats.svelte";
  import WaitBox from "./lib/WaitBox.svelte";
  import type { StatusData } from "./interfaces";

  const apiUrl = window.location.host.split(":")[0] == "localhost" ? "http://fritzgate/api/" : "/api/";
  let data: StatusData;
  let busy = false;
  let timer: NodeJS.Timeout;

  function requestNotifications() {
    Notification.requestPermission(function (result) {
      if (result === "granted") {
        // new Notification("Notifications permission granted")
      }
    });
  }

  async function fetchData() {
    const controller = new AbortController();
    const timeoutId = setTimeout(() => {
      controller.abort();
      busy = true;
    }, 1000);
    try {
      const sensorsJson = await fetch(apiUrl + "status", {
        signal: controller.signal,
      });
      const newData: StatusData = await sensorsJson.json();
      // fix rssi 0 to undefined (not connected)
      newData?.sensors?.forEach((s: any) => (s.rssi = s.rssi ? s.rssi : undefined!));
      if (data) {
        var newSensors = newData.sensors.filter((v) => !data.sensors.find((ns) => ns.name == v.name));
        if (newSensors.length > 0) {
          new Notification("Found a new sensor(s): " + newSensors.map((v) => v.name).join(", "));
        }
      }
      data = newData;
      busy = false;
    } catch {
      // request failed
    } finally {
      clearTimeout(timeoutId);
      timer = setTimeout(fetchData, 2000);
    }
  }
  fetchData();
</script>

<main>
  <nav>
    <ul>
      <li>
        <strong>FritzGate</strong>
        <span aria-busy={busy}></span>
      </li>
    </ul>
    <ul>
      <li><button on:click={requestNotifications}>Notifications</button></li>
      <li><a use:active class="secondary" href="/sensors">Sensors</a></li>
      <li><a use:active class="secondary" href="/heating">Heating</a></li>
    </ul>
  </nav>
  {#if !data}
    <WaitBox message="trying to connect to the FritzGate" details="this buddy gossips too much with sensors" />
  {:else}
    <Route path="/" redirect="/sensors" />
    <Route path="/sensors"><PageSensors {apiUrl} {data} /></Route>
    <Route path="/heating"><PageThermostats {apiUrl} {data} /></Route>
    <Route path="/setup"><PageRouterLogin {apiUrl} {data} /></Route>
  {/if}
</main>
