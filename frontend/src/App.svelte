<script lang="ts">
  import "./app.scss";
  import { Route, active } from "tinro";

  import PageRouterLogin from "./Pages/PageRouterLogin.svelte";
  import PageSensors from "./Pages/PageSensors.svelte";
  import PageThermostats from "./Pages/PageThermostats.svelte";
  import WaitBox from "./lib/WaitBox.svelte";
  import type { ApiService, SensorStatus, StatusData } from "./interfaces";
  import github from "./assets/github-mark.svg";

  export let api: ApiService;
  export let baseUrl: string;
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
    try {
      const newData: StatusData | undefined = await api.fetchStatus();
      if (!newData) {
        busy = true;
        return;
      }

      newData.sensors?.forEach((s) => {
        // fix rssi 0 to undefined (not connected)
        s.rssi = s.rssi ? s.rssi : undefined!;
      });

      if (data) {
        var newSensors = newData.sensors.filter(
          (v) => !data.sensors.find((ns) => ns.name == v.name)
        );
        if (newSensors.length > 0) {
          new Notification(
            "Found a new sensor(s): " + newSensors.map((v) => v.name).join(", ")
          );
        }
      }
      data = newData;
      busy = false;
    } catch {
      busy = true;
      // request failed
    } finally {
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
      <!-- <li><button on:click={requestNotifications}>Notifications</button></li> -->
      <li>
        <a use:active class="secondary" href={baseUrl + "/sensors"}>Sensors</a>
      </li>
      <li>
        <a use:active class="secondary" href={baseUrl + "/heating"}>Heating</a>
      </li>
      <li>
        <a
          use:active
          class="secondary"
          href="https://github.com/vnau/FritzGate"
          target="_blank"
          ><img
            src={github}
            alt="Github"
            style="height: 1.5em; width: 1.5em;"
          /></a
        >
      </li>
    </ul>
  </nav>
  {#if !data}
    <WaitBox
      message="trying to connect to the FritzGate"
      details="this buddy gossips too much with sensors"
    />
  {:else}
    <Route path={baseUrl + "/"} redirect={baseUrl + "/sensors"} />
    <Route path={baseUrl + "/sensors"}><PageSensors {data} /></Route>
    <Route path={baseUrl + "/heating"}
      ><PageThermostats {api} {data} {baseUrl} /></Route
    >
    <Route path={baseUrl + "/setup"}
      ><PageRouterLogin {api} {data} {baseUrl} /></Route
    >
  {/if}
</main>
