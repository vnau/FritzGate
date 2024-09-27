<script lang="ts">
  import { fade } from "svelte/transition";
  import { elasticOut } from "svelte/easing";
  import { onMount } from "svelte";
  export let value: number;
  export let min: number = 0;
  export let max: number = 100;
  export let stroke = 20;
  export let title = "";
  export let titleLeft = "";
  export let titleRight = "";
  export let border = !!title || !!titleLeft || !!titleRight ? 16 : 0;
  let clientWidth: number;
  let clientHeight: number;
  let visible = false;

  onMount(async () => {
    visible = true;
  });

  function spin(node: any) {
    return {
      duration: 1000 + Math.random() * 300,
      css: (t: number) => {
        const eased = elasticOut(t);
        return `transform:  rotate(${eased * 360}deg); transform-origin: 50% 50%;`;
      },
    };
  }

  const valueToAngle = (value: number) => (2 * Math.PI * (Math.max(min, Math.min(max, value)) - min)) / (max - min);
  const calcAngX = (radius: number, stroke: number, angle: number) => radius - (radius - stroke) * Math.sin(angle);
  const calcAngY = (radius: number, stroke: number, angle: number) => radius + (radius - stroke) * Math.cos(angle);

  const calcX = (radius: number, stroke: number, value: number) =>
    Math.round(calcAngX(radius, stroke, valueToAngle(value)) * 1000) / 1000;

  const calcY = (radius: number, stroke: number, value: number) =>
    Math.round(calcAngY(radius, stroke, valueToAngle(value)) * 1000) / 1000;

  const calcCurve = (radius: number, border: number, a: number, b: number) =>
    `M ${calcAngX(radius, border, a)} ${calcAngY(radius, border, a)} A 
    ${radius - border} ${radius - border} 
    0 ${b - a > Math.PI ? 1 : 0} 1 ${calcAngX(radius, border, b)} ${calcAngY(radius, border, b)}`;
</script>

<div
  class="slider-container"
  bind:clientWidth
  bind:clientHeight
  style="--slider-stroke: {stroke}px; --slider-border: {border}px; --slider-radius:{Math.min(
    clientWidth,
    clientHeight,
  ) / 2}px"
  id="sliderHandle"
>
  {#if clientWidth >= 0 && clientHeight >= 0}
    {@const radius = Math.min(clientWidth, clientHeight) / 2}
    {@const border2 = border + stroke / 2}
    {@const x = calcX(radius, border2, value)}
    {@const y = calcY(radius, border2, value)}

    <svg class="slider-svg" style="" xmlns="http://www.w3.org/2000/svg">
      <circle class="slider-circle" cx={radius} cy={radius} r={radius - stroke / 2 - border} />
      <path class="slider-arc" d={calcCurve(radius, border2, 0, valueToAngle(value))} />
      <circle class="slider-handle" cx={x} cy={y} r={stroke / 2} />

      {#if visible}
        <g in:spin>
          <path
            class="slider-title-curve"
            id="curveTop"
            d={calcCurve(radius, border - 2, (2 * Math.PI) / 3, (4 * Math.PI) / 3)}
          />
          <text
            ><textPath class="slider-title" xlink:href="#curveTop" startOffset="50%" text-anchor="middle"
              >{title}</textPath
            ></text
          >
          <path class="slider-title-curve" id="curveLeft" d={calcCurve(radius, border - 2, 0, (2 * Math.PI) / 3)} />
          <text
            ><textPath
              class="slider-title slider-title-secondary"
              xlink:href="#curveLeft"
              startOffset="50%"
              text-anchor="middle">{titleLeft}</textPath
            ></text
          >
          <path
            class="slider-title-curve"
            id="curveRight"
            d={calcCurve(radius, border - 2, (4 * Math.PI) / 3, 2 * Math.PI)}
          />
          <text
            ><textPath
              class="slider-title slider-title-secondary"
              xlink:href="#curveRight"
              startOffset="50%"
              text-anchor="middle">{titleRight}</textPath
            ></text
          >
        </g>
      {/if}
    </svg>
    <div class="slot-container">
      <slot class="" />
    </div>
  {/if}
</div>

<!-- <p>Value: {value}</p> -->

<style>
  .slider-svg {
    /* width: (100% - 2 * var(--slider-border));
    height: (100% - 2 * var(--slider-border));*/
    /* position: absolute; */
    /* width: calc(2 * var(--slider-radius));
    height: calc(2 * var(--slider-radius)); */
    /*margin: var(--slider-border);*/

    width: 100%;
    height: 100%;
    position: absolute;
  }

  .slider-container {
    /* position: relative; */

    width: 100%;
    height: 100%;
    /* border-radius: 50%;
    -webkit-border-radius: 50%;
    overflow: hidden; */
  }

  .slider-circle {
    fill: white;
    stroke: var(--stroke-color);
    /* strgb(203, 14, 14) lightgray; */
    opacity: 30%;
    stroke-width: var(--slider-stroke);
  }

  .slider-arc {
    fill: none;
    stroke: var(--stroke-color);
    stroke-width: var(--slider-stroke);
    stroke-linecap: round;
  }

  .slot-container {
    position: absolute;
    width: 100%;
    height: 100%;
    /* font-size: var(--slider-radius); */
    padding: calc(var(--slider-stroke) + var(--slider-border));

    /* position: absolute;
    width: calc(100% - 2 * var(--slider-border));
    height: calc(100% - 2 * var(--slider-border));
    margin: calc(var(--slider-stroke) + var(--slider-border)); */
  }
  .slider-handle {
    fill: white;
    stroke: var(--stroke-color);
    stroke-width: 1px;
  }

  .slider-title-curve {
    fill: none;
    stroke: none;
  }

  .slider-title.slider-title-secondary {
    font-size: 14px;
    color: lightslategray;
  }

  .slider-title {
    font-family: "Calibri", sans-serif;
    font-size: 20px;
    font-weight: 200;
  }
</style>
