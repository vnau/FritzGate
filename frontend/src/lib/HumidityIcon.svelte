<script lang="ts">
  import iconError from "../assets/humidity.svg";
  import icon0 from "../assets/humidity_low.svg";
  import icon1 from "../assets/humidity_mid.svg";
  import icon2 from "../assets/humidity_high.svg";
  import RangeIcon from "./RangeIcon.svelte";

  export let value: number | undefined | null;
</script>

<RangeIcon
  icons={[icon0, icon1, icon2]}
  min={20}
  max={80}
  undefinedIcon={iconError}
  {value}
  displayValue={value === undefined || value === null
    ? "undefined"
    : value + "%"}
/>
