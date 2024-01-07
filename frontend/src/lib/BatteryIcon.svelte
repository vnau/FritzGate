<script lang="ts">
  import iconError from "../assets/battery_error.svg";
  import icon0 from "../assets/battery_0.svg";
  import icon1 from "../assets/battery_1.svg";
  import icon2 from "../assets/battery_2.svg";
  import icon3 from "../assets/battery_3.svg";
  import icon4 from "../assets/battery_4.svg";
  import icon5 from "../assets/battery_5.svg";
  import icon6 from "../assets/battery_6.svg";
  import icon7 from "../assets/battery_7.svg";
  import RangeIcon from "./RangeIcon.svelte";

  export let value: number | undefined | null;
</script>

<RangeIcon
  icons={[icon0, icon1, icon2, icon3, icon4, icon5, icon6, icon7]}
  min={0}
  max={100}
  undefinedIcon={iconError}
  {value}
  displayValue={value === undefined || value === null
    ? "undefined"
    : value + "%"}
/>
