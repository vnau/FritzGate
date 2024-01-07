<script lang="ts">
  import iconError from "../assets/signal_error.svg";
  import icon0 from "../assets/signal_0.svg";
  import icon1 from "../assets/signal_1.svg";
  import icon2 from "../assets/signal_2.svg";
  import icon3 from "../assets/signal_3.svg";
  import icon4 from "../assets/signal_4.svg";
  import RangeIcon from "./RangeIcon.svelte";

  export let value: number | undefined | null;
</script>

<RangeIcon
  icons={[icon0, icon1, icon2, icon3, icon4]}
  min={-100}
  max={-60}
  undefinedIcon={iconError}
  {value}
  displayValue={value === undefined || value === null
    ? "disconnected"
    : value + " dB"}
/>
