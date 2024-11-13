<script lang="ts">
  import temperatureIcon from "../assets/thermometer.svg";
  import RangeIcon from "./RangeIcon.svelte";

  export let value: number | undefined | null;
</script>

<RangeIcon
  icons={[temperatureIcon]}
  undefinedIcon={temperatureIcon}
  min={10}
  max={30}
  {value}
  displayValue={value === undefined || value === null
    ? "undefined"
    : value?.toLocaleString(undefined, {
        minimumFractionDigits: 1,
        maximumFractionDigits: 1,
      }) + "℃"}
/>