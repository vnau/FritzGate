<script lang="ts">
  import iotSvg from "../assets/iot.svg";

  export let message: string;
  export let details: string;
</script>

<article class="message-splash">
  <hgroup>
    <img src={iotSvg} class="wait-image" alt="" />
    <h4>{message}</h4>
    <p>{details}</p>
  </hgroup>
  <progress></progress>
</article>
