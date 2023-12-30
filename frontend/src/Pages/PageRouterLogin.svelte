<script lang="ts">
  import { onMount } from "svelte";
  import { router } from "tinro";
  import iotSvg from "../assets/iot.svg";
  import WaitBox from "../lib/WaitBox.svelte";

  export let apiUrl: string;
  export let data: any;

  let host: string;
  let pass: string;
  let status: string;
  let user: string;

  let submitForm = async (e: any): Promise<boolean> => {
    console.log("submit");
    await fetch(apiUrl + "fritzauth", {
      method: "POST",
      body: JSON.stringify({ host, user, pass }),
    });
    status = "CONFIGURED";
    return false;
  };

  $: {
    if (
      status &&
      status !== data?.fritz?.status &&
      data?.fritz?.status === "CONNECTED"
    ) {
      router.goto("/heating");
    } else {
      status = data?.fritz?.status;
      host ??= data?.fritz?.host;
      user ??= data?.fritz?.user;
    }
  }

  onMount(async function () {
    ({ host, user } = data?.fritz);
  });
</script>

{#if status === "CONFIGURED" || status === "CONNECTING"}
  <WaitBox
    message="connecting to FRITZ!Box"
    details="please wait, this may take a while"
  />
{:else}
  <article>
    <hgroup>
      <div class="message-splash">
        <img src={iotSvg} class="wait-image" alt="" />
        <h4>
          {status === "CONNECTED"
            ? "update credentials for FRITZ!Box"
            : "connect to FRITZ!Box"}
        </h4>
        <p>
          Set up a hostname (in most cases <i>fritz.box</i> or
          <i>192.168.178.1</i>), username and password to connect to the
          FRITZ!Box SmartHome.
        </p>
      </div>
    </hgroup>
    {#if status === "FAILURE"}
      <center
        ><p>
          <mark
            >failed to connect to FRITZ!Box with the provided credentials</mark
          >
        </p></center
      >
    {/if}
    <form on:submit|preventDefault={submitForm} autocomplete="off">
      <input
        type="text"
        name="ip"
        placeholder="Router address (should be 192.168.179.1 or fritz.box for most FRITZ!Boxes)"
        required
        bind:value={host}
        autocomplete="off"
      />
      <input
        type="text"
        name="login"
        placeholder="FRITZ!Box username"
        required
        bind:value={user}
        autocomplete="off"
      />
      <input
        type="password"
        name="pass"
        placeholder="Password"
        required
        bind:value={pass}
        autocomplete="off"
      />

      <input type="submit" value="Connect FritzGate to FRITZ!Box" />
    </form>
  </article>
{/if}
